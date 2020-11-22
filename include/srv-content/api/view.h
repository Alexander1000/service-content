#ifndef SRV_CONTENT_API_VIEW_H
#define SRV_CONTENT_API_VIEW_H

#include <socketer.h>
#include <srv-content/storage.h>
#include <json-stream-analyzer.h>
#include <srv-content/models/view.h>

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
        void error_response(Socketer::Response* resp, int code, char* message);
        static Request* parse_request(Socketer::Request* request);
        JsonStreamAnalyzer::Element* encode_view_to_json(Content::Model::View* view);
    };
}

#endif
