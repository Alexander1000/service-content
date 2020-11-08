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

    void SaveHandler::on_request(Socketer::Request *request, Socketer::Response* resp)
    {
        std::cout << "/v1/save called" << std::endl;

        std::cout << "Raw body: [" << request->raw_body << "]" << std::endl;

        resp->writeHead("HTTP/1.1 204 No Content");
        resp->addHeader("Server", "service-content/1.0.0");
        resp->reply();
    }
}
