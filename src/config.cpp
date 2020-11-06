#include <srv-content/config.h>
#include <string>
#include <map>

#include <io-buffer.h>
#include <json-stream-analyzer.h>

namespace Content
{
    Config::Config(int argc, char **argv)
    {
        this->is_help = false;

        for (int i = 1; i < argc; i++) {
            std::string paramName(argv[i]);

            if (paramName == "-h" || paramName == "--help") {
                this->is_help = true;
                continue;
            }

            if (paramName == "-c" || paramName == "--config") {
                if (i + 1 == argc) {
                    // todo: error missed argument value
                    continue;
                }
                std::string paramValue(argv[i+1]);
                this->parse_config_file(paramValue);
                i++;
                continue;
            }
        }
    }

    void Config::parse_config_file(std::string file_name)
    {
        IOBuffer::IOFileReader fileReader(file_name.c_str());
        IOBuffer::CharStream charStream(&fileReader);
        JsonStreamAnalyzer::Stream stream(&charStream);
        JsonStreamAnalyzer::Decoder decoder(&stream);

        JsonStreamAnalyzer::Element* element = decoder.decode();

        if (element->getType() == ELEMENT_TYPE_OBJECT) {
            JsonObject* obj = (JsonObject*) element->getData();

            if (obj->find("server") != obj->end()) {
                JsonStreamAnalyzer::Element* serverConfig = obj->at("server");
                if (serverConfig->getType() == ELEMENT_TYPE_OBJECT) {
                    // parse server object
                    JsonObject* serverJsonObj = (JsonObject*) serverConfig->getData();

                    if (serverJsonObj->find("listen") != serverJsonObj->end()) {
                        JsonStreamAnalyzer::Element* eListenIp = serverJsonObj->at("listen");
                        if (eListenIp->getType() == ELEMENT_TYPE_TEXT) {
                            std::string* listen = (std::string*) eListenIp->getData();
                            this->listen = *listen;
                        }
                    }

                    if (serverJsonObj->find("port") != serverJsonObj->end()) {
                        JsonStreamAnalyzer::Element* ePort = serverJsonObj->at("port");
                        if (ePort->getType() == ELEMENT_TYPE_NUMERIC) {
                            std::string *sPort = (std::string*) ePort->getData();
                            this->port = atoi(sPort->c_str());
                        }
                    }
                }
            }
        }
    }

    int Config::get_port() {
        return this->port;
    }

    std::string Config::get_listen() {
        return this->listen;
    }

    bool Config::isHelp() {
        return this->is_help;
    }
}
