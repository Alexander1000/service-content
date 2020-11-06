#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <iostream>
#include <map>


#include <srv-content/config.h>
#include <srv-content/storage.h>
#include <srv-content/connection.h>

const short  SERVER_BACKLOG    = 128;

Content::Config* config = nullptr;

class RequestHead
{
public:
    RequestHead(char* method, char* uri, char* protocol) {
        this->method = method;
        this->uri = uri;
        this->protocol = protocol;
    }

    char* method;
    char* uri;
    char* protocol;
};

void on_request(char* request_raw, int requestLength, int socketfd);

int main(int argc, char** argv) {
    config = new Content::Config(argc, argv);

    if (config->isHelp()) {
        std::cout << "It is help message" << std::endl;
        return 0;
    }

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        std::cout << "Error socket(): " << strerror(errno) << std::endl;
        return 1;
    }

    u_short      port  = config->get_port();
    const char * host  = config->get_listen().c_str();
    sockaddr_in  sa;
    bzero(&sa, sizeof(sa));
    int          on    = 1;
    sa.sin_family      = AF_INET;
    sa.sin_port        = htons(port);
    sa.sin_addr.s_addr = inet_addr(host);

    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
        std::cout << "Error setsockopt(): " << strerror(errno) << std::endl;
        return 1;
    }

    // Bind server socket to ip:port
    if (bind(server_sock, (const sockaddr*)&sa, sizeof(sa)) == -1) {
        std::cout << "Error bind(): " << strerror(errno) << " on: " << host << ":" << port << std::endl;
        return 1;
    }

    // Make server to listen
    if (listen(server_sock, SERVER_BACKLOG) == -1) {
        std::cout << "Error listen(): " << strerror(errno) << std::endl;
        return 1;
    }

    int clilen = sizeof(struct sockaddr);
    struct sockaddr cli_addr;

    int newsockfd;

    while (1) {
        newsockfd = accept(server_sock, &cli_addr, (socklen_t*) &clilen);

        if (newsockfd < 0) {
            std::cout << "Error! On Accepting Request! i.e. requests limit crossed" << std::endl;
        }

        int pid = fork();
        if (pid == 0) {
            std::cout << "Spawn worker" << std::endl;

            int maxBufferSize = 4096;

            char buf[maxBufferSize];
            memset(buf, 0, maxBufferSize * sizeof(char));

            char* requestMessage = (char*) malloc(maxBufferSize);
            requestMessage[0] = '\0';

            int totalReceivBits = 0;

            while (strstr(requestMessage, "\r\n\r\n") == NULL) {
                int recvd = recv(newsockfd, buf, maxBufferSize, 0);
                if (recvd < 0) {
                    std::cout << "Error while receiving data" << std::endl;
                    return 2;
                } else if (recvd == 0) {
                    break;
                } else {
                    totalReceivBits += recvd;

                    buf[recvd] = '\0';
                    if (totalReceivBits > maxBufferSize) {
                        maxBufferSize *= 2;
                        requestMessage = (char*) realloc(requestMessage, maxBufferSize);
                    }
                }

                strcat(requestMessage, buf);
            }

            on_request(requestMessage, totalReceivBits, newsockfd);

            close(newsockfd);
            break;
        }
    }

    close(server_sock);

    return 0;
}

/**
 * example:
 * ====================
 * POST /test HTTP/1.1
 * Host: 127.0.0.1:50101
 * Accept:
 * User-Agent: curlik
 * Content-Length: 6
 * Content-Type: application/x-www-form-urlencoded
 * ====================
 * @param request_raw
 * @param requestLength
 * @return
 */
std::map<std::string, std::string>* parse_headers(char* request_raw, int requestLength) {
    std::map<std::string, std::string>* headers;
    headers = new std::map<std::string, std::string>;

    // skip head of request
    int i = 0;
    while (request_raw[i++] != '\n') {}

    int cur_pos = i;

    do {
        int start_pos_header_name = cur_pos;
        int j = start_pos_header_name;
        while (request_raw[j++] != ':') {}
        char *header_name;
        header_name = new char[j - start_pos_header_name];
        memset(header_name, 0, sizeof(char) * (j - start_pos_header_name));
        memcpy(header_name, request_raw + start_pos_header_name, sizeof(char) * (j - start_pos_header_name - 1));

        j++; // skip space

        int start_pos_header_value = j;
        while (request_raw[j++] != '\n') {}
        char *header_value;
        header_value = new char[j - start_pos_header_value];
        memset(header_value, 0, sizeof(char) * (j - start_pos_header_value));
        memcpy(header_value, request_raw + start_pos_header_value, sizeof(char) * (j - start_pos_header_value - 1));

        (*headers)[std::string(header_name)] = std::string(header_value);

        cur_pos = j - 1;

        if (request_raw[cur_pos] == '\n' && request_raw[cur_pos + 1] == '\r') {
            break;
        }

        cur_pos++;

        if (cur_pos >= requestLength) {
            break;
        }
    } while(true);

    return headers;
}

/**
 * @example: POST /test HTTP/1.1
 * @param request_raw
 */
RequestHead* parse_head(char* request_raw) {
    int i = 0;
    while (request_raw[i++] != ' ') {}

    char* method;
    method = new char[i];
    memset(method, 0, sizeof(char) * i);
    memcpy(method, request_raw, sizeof(char) * i);

    int start = i;
    while (request_raw[i++] != ' ') {}
    char* uri;
    uri = new char[i - start];
    memset(uri, 0, sizeof(char) * (i - start));
    memcpy(uri, request_raw + start, sizeof(char) * (i - start));

    start = i;
    while (request_raw[i++] != '\n') {}
    char* protocol;
    protocol = new char[i - start];
    memset(protocol, 0, sizeof(char) * (i - start));
    memcpy(protocol, request_raw + start, sizeof(char) * (i - start));

    RequestHead* r;
    r = new RequestHead(method, uri, protocol);
    return r;
}

void on_request_v1_save(RequestHead* r, char* request_raw, int requestLength, int socketfd) {
    std::cout << "/v1/save called" << std::endl;

    std::string http_response = "HTTP/1.1 204 No Content\n";
    write(socketfd, http_response.c_str(), sizeof(char) * http_response.length());

    std::string http_server = "Server: service-content/1.0.0\n";
    write(socketfd, http_server.c_str(), sizeof(char) * http_server.length());

    write(socketfd, "\n\r\n\r", sizeof(char) * 8);
}

void on_request(char* request_raw, int requestLength, int socketfd) {
    std::cout << request_raw << std::endl;

    RequestHead* r = parse_head(request_raw);

    std::map<std::string, std::string>* headers = parse_headers(request_raw, requestLength);

    std::string method(r->method);
    std::string uri(r->uri);

    std::cout << "URI: [" << uri << "]" << std::endl;
    std::cout << "Method: [" << method << "]" << std::endl;

    if (uri == "/v1/save" && method == "POST") {
        on_request_v1_save(r, request_raw, requestLength, socketfd);
        return;
    }

    Content::DBConn db_conn(
        config->getDbHost(),
        config->getDbPort(),
        config->getDbUser(),
        config->getDbPassword(),
        config->getDbName()
    );
    Content::Storage s(&db_conn);

    int content_id = 7;
    s.save_content(&content_id, (char*) "test title", (char*) "text of content", 1);

    std::string http_response = "HTTP/1.1 204 No Content\n";
    write(socketfd, http_response.c_str(), sizeof(char) * http_response.length());

    std::string http_server = "Server: service-content/1.0.0\n";
    write(socketfd, http_server.c_str(), sizeof(char) * http_server.length());

    write(socketfd, "\n\r\n\r", sizeof(char) * 8);
}
