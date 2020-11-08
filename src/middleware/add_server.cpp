#include <srv-content.h>

namespace Content::Middleware
{
    void AddServer::on_request(Socketer::Request *req, Socketer::Response *resp)
    {
        resp->addHeader("Server", "service-content/1.0.0");
    }
}
