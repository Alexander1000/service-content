#ifndef SRV_CONTENT_CONFIG_H
#define SRV_CONTENT_CONFIG_H

#include <string>

namespace Content
{
    class Config
    {
    public:
        Config(int argc, char **argv);
    private:
        bool is_help;

        void parse_config_file(std::string file_name);
    };
}

#endif
