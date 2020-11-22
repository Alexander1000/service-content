#include <srv-content.h>

namespace Content::API::View
{
    Handler::Handler(Content::Storage *storage)
    {
        this->storage = storage;
    }

    void Handler::on_request(Socketer::Request *request, Socketer::Response *response)
    {
        if (std::string(request->method) != "POST") {
            response->writeHead("HTTP/1.1 405 Method not allowed");
            response->addHeader("Content-Type", "application/json");
            this->error_response(response, 405, (char*) "Method not allowed");
            response->reply();
            return;
        }

        if (std::string(request->headers["Content-Type"]) != "application/json") {
            response->writeHead("HTTP/1.1 405 Method not allowed");
            response->addHeader("Content-Type", "application/json");
            this->error_response(response, 405, (char*) "Method not allowed");
            response->reply();
            return;
        }

        auto reqView = Content::API::View::Handler::parse_request(request);

        auto view = this->storage->get_view_by_slug(reqView->slug);

        if (view == nullptr) {
            response->writeHead("HTTP/1.1 404 Not found");
            response->addHeader("Content-Type", "application/json");
            this->error_response(response, 404, (char*) "Not found");
            response->reply();
            return;
        }

        response->writeHead("HTTP/1.1 200 OK");
        response->addHeader("Content-Type", "application/json; charset=utf-8");
        response->reply();
    }
}
