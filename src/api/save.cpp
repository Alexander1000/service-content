#include <iostream>
#include <socketer.h>
#include <srv-content.h>

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

        resp->writeHead("HTTP/1.1 200 OK");
        resp->write((void*) "Hello world", 11);
        resp->reply();
    }
}
