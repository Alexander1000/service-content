#include <iostream>
#include <socketer.h>
#include <srv-content.h>
#include <unistd.h>
#include <string>

namespace Content::API
{
    SaveHandler::SaveHandler(Content::Storage *storage)
    {
        this->storage = storage;
    }

    void SaveHandler::on_request(Socketer::Request *request, int socket)
    {
        std::cout << "/v1/save called" << std::endl;

        std::cout << "Raw body: [" << request->raw_body << "]" << std::endl;

        std::string http_response = "HTTP/1.1 204 No Content\r\n";
        write(socket, http_response.c_str(), sizeof(char) * http_response.length());

        std::string http_server = "Server: service-content/1.0.0\r\n";
        write(socket, http_server.c_str(), sizeof(char) * http_server.length());

        write(socket, "\r\n\r\n", sizeof(char) * 4);
    }
}
