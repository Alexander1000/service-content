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

        // set defaults
        this->db_host = "127.0.0.1";
        this->db_port = 5432;
        this->db_user = "postgres";
        this->db_password = nullptr;
        this->db_name = "postgres";

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

            if (obj->find("database") != obj->end()) {
                JsonStreamAnalyzer::Element* databaseConfig = obj->at("database");
                if (databaseConfig->getType() == ELEMENT_TYPE_OBJECT) {
                    auto databaseConfigObj = (JsonObject*) databaseConfig->getData();

                    if (databaseConfigObj->find("host") != databaseConfigObj->end()) {
                        JsonStreamAnalyzer::Element* elDbHost = databaseConfigObj->at("host");
                        if (elDbHost->getType() == ELEMENT_TYPE_TEXT) {
                            auto dbHost = (std::string*) elDbHost->getData();
                            this->db_host = *dbHost;
                        }
                    }

                    if (databaseConfigObj->find("port") != databaseConfigObj->end()) {
                        JsonStreamAnalyzer::Element* elDbPort = databaseConfigObj->at("port");
                        if (elDbPort->getType() == ELEMENT_TYPE_NUMERIC) {
                            auto dbPort = (std::string*) elDbPort->getData();
                            this->db_port = atoi(dbPort->c_str());
                        }
                    }

                    if (databaseConfigObj->find("user") != databaseConfigObj->end()) {
                        JsonStreamAnalyzer::Element* elDbUser = databaseConfigObj->at("user");
                        if (elDbUser->getType() == ELEMENT_TYPE_TEXT) {
                            auto dbUser = (std::string*) elDbUser->getData();
                            this->db_user = *dbUser;
                        }
                    }

                    if (databaseConfigObj->find("password") != databaseConfigObj->end()) {
                        JsonStreamAnalyzer::Element* elDbPassword = databaseConfigObj->at("password");
                        if (elDbPassword->getType() == ELEMENT_TYPE_TEXT) {
                            auto dbPassword = (std::string*) elDbPassword->getData();
                            this->db_password = dbPassword;
                        }
                    }

                    if (databaseConfigObj->find("name") != databaseConfigObj->end()) {
                        JsonStreamAnalyzer::Element* elDbName = databaseConfigObj->at("name");
                        if (elDbName->getType() == ELEMENT_TYPE_TEXT) {
                            auto dbName = (std::string*) elDbName->getData();
                            this->db_name = *dbName;
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

    std::string Config::getDbHost() {
        return this->db_host;
    }

    int Config::getDbPort() {
        return this->db_port;
    }

    std::string Config::getDbUser() {
        return this->db_user;
    }

    std::string* Config::getDbPassword() {
        return this->db_password;
    }

    std::string Config::getDbName() {
        return this->db_name;
    }
}
