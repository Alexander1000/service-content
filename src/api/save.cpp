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
        if (std::string(request->method) != "POST") {
            resp->writeHead("HTTP/1.1 405 Method not allowed");
            resp->addHeader("Content-Type", "application/json");
            std::string errResp = "{\"error\":{\"code\":405,\"message\":\"Method not allowed\"}}";
            resp->write((void*) errResp.c_str(), errResp.length());
            resp->reply();
            return;
        }
        std::cout << "/v1/save called" << std::endl;

        std::cout << "Raw body: [" << request->raw_body << "]" << std::endl;

        resp->writeHead("HTTP/1.1 200 OK");
        resp->write((void*) "Hello world", 11);
        resp->reply();
    }
}
