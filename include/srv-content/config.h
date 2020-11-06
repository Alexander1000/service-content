#ifndef SRV_CONTENT_CONFIG_H
#define SRV_CONTENT_CONFIG_H

#include <string>
#include <json-stream-analyzer.h>

typedef std::map<std::string, JsonStreamAnalyzer::Element *> JsonObject;

namespace Content
{
    class Config
    {
    public:
        Config(int argc, char **argv);
        int get_port();
        std::string get_listen();
        bool isHelp();
    private:
        bool is_help;
        std::string listen;
        int port;

        std::string db_host;
        int db_port;
        std::string db_user;
        std::string* db_password;
        std::string db_name;

        void parse_config_file(std::string file_name);
    };
}

#endif
