#ifndef SRV_CONTENT_MIDDLEWARE_H
#define SRV_CONTENT_MIDDLEWARE_H

#include <list>
#include <socketer.h>

namespace Content::Middleware
{
    class Middleware
    {
    public:
        virtual void on_request(Socketer::Request* req, Socketer::Response* resp) = 0;
    };

    class AddServer : Middleware
    {
    public:
        void on_request(Socketer::Request* req, Socketer::Response* resp);
    };

    class Chain : Middleware
    {
    public:
        Chain();
        void on_request(Socketer::Request* req, Socketer::Response* resp);

        std::list<Middleware*> chain;
    };
}

#endif
