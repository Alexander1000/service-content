#include <string>
#include <srv-content.h>
#include <json-stream-analyzer.h>

namespace Content::API::View
{
    void Handler::error_response(Socketer::Response* resp, int code, char *message)
    {
        std::string strCode = std::to_string(code);
        JsonStreamAnalyzer::Element elCode(ELEMENT_TYPE_TEXT, &strCode);

        std::string strMessage = message;
        JsonStreamAnalyzer::Element elMessage(ELEMENT_TYPE_TEXT, &strMessage);

        JsonObject errObj;
        errObj["code"] = &elCode;
        errObj["message"] = &elMessage;

        JsonStreamAnalyzer::Element elErrObj(ELEMENT_TYPE_OBJECT, &errObj);

        JsonObject resultObj;
        resultObj["error"] = &elErrObj;

        JsonStreamAnalyzer::Element elResult(ELEMENT_TYPE_OBJECT, &resultObj);

        JsonStreamAnalyzer::Encoder encoder;

        std::string* strResult = encoder.encode(&elResult);

        resp->write((void*) strResult->c_str(), strResult->length());
    }
}
