#include <srv-content.h>
#include <io-buffer.h>
#include <json-stream-analyzer.h>

namespace Content::API::Page
{
    RequestSave* SaveHandler::parse_request(Socketer::Request* request) {
        IOBuffer::IOMemoryBuffer memoryBuffer;
        memoryBuffer.write(request->raw_body, strlen(request->raw_body));
        memoryBuffer.setPosition(0);

        IOBuffer::CharStream charStream(&memoryBuffer);
        JsonStreamAnalyzer::Stream stream(&charStream);
        JsonStreamAnalyzer::Decoder decoder(&stream);

        JsonStreamAnalyzer::Element* element = decoder.decode();

        RequestSave* reqSave = nullptr;
        reqSave = new RequestSave;

        if (element->getType() == ELEMENT_TYPE_OBJECT) {
            auto obj = (JsonObject*) element->getData();
            if (obj->find("id") != obj->end()) {
                auto elId = obj->at("id");
                if (elId->getType() == ELEMENT_TYPE_NUMERIC) {
                    auto sId = (std::string*) elId->getData();
                    int id = atoi(sId->c_str());
                    reqSave->id = new int;
                    *reqSave->id = id;
                }
            }
            if (obj->find("slug") != obj->end()) {
                auto elSlug = obj->at("slug");
                if (elSlug->getType() == ELEMENT_TYPE_TEXT) {
                    auto slug = (std::string*) elSlug->getData();
                    reqSave->slug = new char[slug->length() + 1];
                    memset(reqSave->slug, 0, (slug->length() + 1) * sizeof(char));
                    memcpy(reqSave->slug, slug->c_str(), slug->length() * sizeof(char));
                }
            }
            if (obj->find("contentId") != obj->end()) {
                auto elContentId = obj->at("contentId");
                if (elContentId->getType() == ELEMENT_TYPE_NUMERIC) {
                    auto sContentId = (std::string*) elContentId->getData();
                    int contentId = atoi(sContentId->c_str());
                    reqSave->contentId = new int;
                    *reqSave->contentId = contentId;
                }
            }
        }

        return reqSave;
    }
}
