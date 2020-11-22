#ifndef SRV_CONTENT_API_VIEW_H
#define SRV_CONTENT_API_VIEW_H

#include <socketer.h>
#include <srv-content/storage.h>

namespace Content::API::View
{
    class Request
    {
    public:
        char* slug;
    };

    class Handler
    {
    public:
        explicit Handler(Content::Storage* storage);
        void on_request(Socketer::Request* request, Socketer::Response* response);
    private:
        Content::Storage* storage;
    };
}

#endif
