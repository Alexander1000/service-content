#include <srv-content.h>

namespace Content::Middleware
{
    void AddServer::on_request(Socketer::Request *req, Socketer::Response *resp)
    {
        resp->addHeader("Server", std::string("service-content/") + SERVICE_VERSION);
    }
}
