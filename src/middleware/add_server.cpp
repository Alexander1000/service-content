#include <srv-content.h>

namespace Content::Middleware
{
    void add_server(Socketer::Request* req, Socketer::Response* resp)
    {
        resp->addHeader("Server", std::string("service-content/") + SERVICE_VERSION);
    }
}
