#include <srv-content.h>
#include <io-buffer.h>
#include <json-stream-analyzer.h>

namespace Content::API
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
            if (obj->find("title") != obj->end()) {
                auto elTitle = obj->at("title");
                if (elTitle->getType() == ELEMENT_TYPE_TEXT) {
                    auto title = (std::string*) elTitle->getData();
                    reqSave->title = new char[title->length()];
                    memset(reqSave->title, 0, title->length());
                    memcpy(reqSave->title, title->c_str(), title->length() * sizeof(char));
                }
            }
            if (obj->find("text") != obj->end()) {
                auto elText = obj->at("text");
                if (elText->getType() == ELEMENT_TYPE_TEXT) {
                    auto text = (std::string*) elText->getData();
                    reqSave->text = new char[text->length()];
                    memset(reqSave->text, 0, text->length());
                    memcpy(reqSave->text, text->c_str(), text->length() * sizeof(char));
                }
            }
            if (obj->find("userId") != obj->end()) {
                auto elUserId = obj->at("userId");
                if (elUserId->getType() == ELEMENT_TYPE_NUMERIC) {
                    auto sUserId = (std::string*) elUserId->getData();
                    int userId = atoi(sUserId->c_str());
                    reqSave->userId = new int;
                    *reqSave->userId = userId;
                }
            }
        }

        return reqSave;
    }
}
