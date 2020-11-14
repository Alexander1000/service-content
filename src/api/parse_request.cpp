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

        return nullptr;
    }
}
