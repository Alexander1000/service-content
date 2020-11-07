#include <string.h>
#include <unistd.h>

#include <iostream>
#include <map>

#include <srv-content/config.h>
#include <srv-content/storage.h>
#include <srv-content/connection.h>

#include <socketer.h>

Content::Config* config = nullptr;

void on_request(Socketer::Request* request, int socket);
void on_request_v1_save(Socketer::Request* request, int socket);

int main(int argc, char** argv) {
    config = new Content::Config(argc, argv);

    if (config->isHelp()) {
        std::cout << "It is help message" << std::endl;
        return 0;
    }

    Socketer::Socketer server;

    server.listen(config->get_listen(), config->get_port());

    server.addHandler("/v1/save", on_request_v1_save);

    server.setDefaultHandler(on_request);

    server.dispatch();

    return 0;
}

void on_request_v1_save(Socketer::Request* request, int socket) {
    std::cout << "/v1/save called" << std::endl;

    std::cout << "Raw body: [" << request->raw_body << "]" << std::endl;

    std::string http_response = "HTTP/1.1 204 No Content\r\n";
    write(socket, http_response.c_str(), sizeof(char) * http_response.length());

    std::string http_server = "Server: service-content/1.0.0\r\n";
    write(socket, http_server.c_str(), sizeof(char) * http_server.length());

    write(socket, "\r\n\r\n", sizeof(char) * 8);
}

void on_request(Socketer::Request* request, int socket) {
    std::cout << request->raw_body << std::endl;

    std::string method(request->method);
    std::string uri(request->uri);

    std::cout << "URI: [" << uri << "]" << std::endl;
    std::cout << "Method: [" << method << "]" << std::endl;

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

    std::string http_response = "HTTP/1.1 204 No Content\r\n";
    write(socket, http_response.c_str(), sizeof(char) * http_response.length());

    std::string http_server = "Server: service-content/1.0.0\r\n";
    write(socket, http_server.c_str(), sizeof(char) * http_server.length());

    write(socket, "\r\n\r\n", sizeof(char) * 8);
}
