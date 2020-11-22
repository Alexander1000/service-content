#include <socketer.h>
#include <srv-content.h>
#include <io-buffer.h>
#include <json-stream-analyzer.h>

namespace Content::API::View
{
    Request* Handler::parse_request(Socketer::Request *request)
    {
        IOBuffer::IOMemoryBuffer memoryBuffer;
        memoryBuffer.write(request->raw_body, strlen(request->raw_body));
        memoryBuffer.setPosition(0);

        IOBuffer::CharStream charStream(&memoryBuffer);
        JsonStreamAnalyzer::Stream stream(&charStream);
        JsonStreamAnalyzer::Decoder decoder(&stream);

        JsonStreamAnalyzer::Element* element = decoder.decode();

        Request* reqView = nullptr;
        reqView = new Request;

        if (element->getType() == ELEMENT_TYPE_OBJECT) {
            auto obj = (JsonObject*) element->getData();
            if (obj->find("slug") != obj->end()) {
                auto elSlug = obj->at("slug");
                if (elSlug->getType() == ELEMENT_TYPE_TEXT) {
                    auto slug = (std::string*) elSlug->getData();
                    reqView->slug = new char[slug->length() + 1];
                    memset(reqView->slug, 0, (slug->length() + 1) * sizeof(char));
                    memcpy(reqView->slug, slug->c_str(), slug->length() * sizeof(char));
                }
            }
        }

        return reqView;
    }
}
