#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

#include <iostream>

const short  SERVER_BACKLOG    = 128;

void on_request(char* request_raw, int socketfd);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Start as:" << std::endl
                  << argv[0] << " host_address port" << std::endl;
        return 1;
    }

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        std::cout << "Error socket(): " << strerror(errno) << std::endl;
        return 1;
    }

    u_short      port  = atol(argv[2]);
    const char * host  = argv[1];
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

            on_request(requestMessage, newsockfd);

            close(newsockfd);
            break;
        }
    }

    close(server_sock);

    return 0;
}

void on_request(char* request_raw, int socketfd) {
    std::cout << request_raw << std::endl;

    char* http_response = "HTTP/1.1 204 No Content\n";
    write(socketfd, http_response, sizeof(char) * strlen(http_response));

    char* http_server = "Server: service-content/1.0.0\n";
    write(socketfd, http_server, sizeof(char) * strlen(http_server));

    write(socketfd, "\n\r\n\r", sizeof(char) * 8);
}
