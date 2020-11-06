#include <srv-content/config.h>
#include <string>

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
        // do parse
    }
}
