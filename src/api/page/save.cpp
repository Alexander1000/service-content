#include <srv-content.h>
#include <json-stream-analyzer.h>

namespace Content::API::Page
{
    SaveHandler::SaveHandler(Content::Storage *storage)
    {
        this->storage = storage;
    }

    void SaveHandler::on_request(Socketer::Request *request, Socketer::Response *resp) {
        if (std::string(request->method) != "POST") {
            resp->writeHead("HTTP/1.1 405 Method not allowed");
            resp->addHeader("Content-Type", "application/json");
            this->error_response(resp, 405, (char*) "Method not allowed");
            resp->reply();
            return;
        }

        if (std::string(request->headers["Content-Type"]) != "application/json") {
            resp->writeHead("HTTP/1.1 405 Method not allowed");
            resp->addHeader("Content-Type", "application/json");
            this->error_response(resp, 405, (char*) "Method not allowed");
            resp->reply();
            return;
        }

        RequestSave* reqSave = this->parse_request(request);

        bool saveResult = this->storage->save_page(reqSave->id, reqSave->slug, reqSave->contentId);

        JsonStreamAnalyzer::Element elSuccess(ELEMENT_TYPE_BOOL, (void*) saveResult);

        JsonObject resultObj;
        resultObj["success"] = &elSuccess;

        JsonStreamAnalyzer::Element elErrObj(ELEMENT_TYPE_OBJECT, &resultObj);

        JsonObject responseObj;
        responseObj["result"] = &elErrObj;

        JsonStreamAnalyzer::Element elResponse(ELEMENT_TYPE_OBJECT, &responseObj);

        JsonStreamAnalyzer::Encoder encoder;

        std::string* strResult = encoder.encode(&elResponse);

        resp->writeHead("HTTP/1.1 200 OK");
        resp->addHeader("Content-Type", "application/json; charset=utf-8");
        resp->write((void*) strResult->c_str(), strResult->length());
        resp->reply();
    }
}
