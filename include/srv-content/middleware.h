#ifndef SRV_CONTENT_MIDDLEWARE_H
#define SRV_CONTENT_MIDDLEWARE_H

#include <socketer.h>

namespace Content::Middleware
{
    void add_server(Socketer::Request* req, Socketer::Response* resp);
}

#endif
