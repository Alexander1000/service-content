#ifndef SRV_CONTENT_API_SAVE_H
#define SRV_CONTENT_API_SAVE_H

#include <socketer.h>
#include <srv-content/storage.h>

namespace Content::API
{
    class SaveHandler
    {
    public:
        SaveHandler(Content::Storage* storage);
        void on_request(Socketer::Request* request, Socketer::Response* resp);

    private:
        Content::Storage* storage;
    };
}

#endif
