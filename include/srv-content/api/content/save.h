#ifndef SRV_CONTENT_API_SAVE_H
#define SRV_CONTENT_API_SAVE_H

#include <socketer.h>
#include <srv-content/storage.h>

namespace Content::API
{
    class RequestSave
    {
    public:
        RequestSave();

        int* id;
        char* title;
        char* text;
        int* userId;
    };

    class SaveHandler
    {
    public:
        SaveHandler(Content::Storage* storage);
        void on_request(Socketer::Request* request, Socketer::Response* resp);

    private:
        Content::Storage* storage;

        RequestSave* parse_request(Socketer::Request* request);

        void error_response(Socketer::Response* resp, int code, char* message);
    };
}

#endif
