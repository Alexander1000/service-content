#include <iostream>
#include <socketer.h>
#include <srv-content.h>

namespace Content::API
{
    SaveHandler::SaveHandler(Content::Storage *storage)
    {
        this->storage = storage;
    }

    void SaveHandler::on_request(Socketer::Request *request, Socketer::Response* resp)
    {
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

        int contentId = this->storage->save_content(reqSave->id, reqSave->title, reqSave->text, *reqSave->userId);

        resp->writeHead("HTTP/1.1 200 OK");
        resp->addHeader("Content-Type", "application/json; charset=utf-8");

        // response body
        std::string strId = std::to_string(contentId);
        JsonStreamAnalyzer::Element elId(ELEMENT_TYPE_NUMERIC, &strId);

        JsonObject resultObj;
        resultObj["contentId"] = &elId;

        JsonStreamAnalyzer::Element elErrObj(ELEMENT_TYPE_OBJECT, &resultObj);

        JsonObject responseObj;
        responseObj["result"] = &elErrObj;

        JsonStreamAnalyzer::Element elResponse(ELEMENT_TYPE_OBJECT, &responseObj);

        JsonStreamAnalyzer::Encoder encoder;

        std::string* strResult = encoder.encode(&elResponse);

        resp->write((void*) strResult->c_str(), strResult->length());

        resp->reply();
    }
}
