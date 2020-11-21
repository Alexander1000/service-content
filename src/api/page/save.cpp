#include <srv-content.h>

namespace Content::API::Page
{
    SaveHandler::SaveHandler(Content::Storage *storage)
    {
        this->storage = storage;
    }

    void SaveHandler::on_request(Socketer::Request *request, Socketer::Response *resp) {
        if (std::string(request->method) != "POST") {
            resp->writeHead("HTTP/1.1 405 Method not allowed");
            resp->addHeader("Content-Type", "application/json");
            this->error_response(resp, 405, (char*) "Method not allowed");
            resp->reply();
            return;
        }

        if (std::string(request->headers["Content-Type"]) != "application/json") {
            resp->writeHead("HTTP/1.1 405 Method not allowed");
            resp->addHeader("Content-Type", "application/json");
            this->error_response(resp, 405, (char*) "Method not allowed");
            resp->reply();
            return;
        }

        RequestSave* reqSave = this->parse_request(request);

        resp->writeHead("HTTP/1.1 200 OK");
        resp->addHeader("Content-Type", "application/json; charset=utf-8");
        resp->reply();
    }
}
