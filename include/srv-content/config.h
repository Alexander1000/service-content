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
    private:
        bool is_help;

        std::string listen;

        int port;

        void parse_config_file(std::string file_name);
    };
}

#endif
