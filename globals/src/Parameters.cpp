#include "Parameters.h"

namespace parameters {

    Config::Config(): config_file_("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot_build\\bin\\config.ini"), opts_("Default Config"), variables_map_()
    {
        this->setOptions();
        this->parseFile();
    }

    void Config::setOptions()
    {
        this->opts_.add_options()
            ("camera.device_id", po::value<int>())
            ("detection.live_threshold", po::value<int>());
    }

    void Config::parseFile()
    {
        const bool ALLOW_UNREGISTERED = true;
        std::ifstream ifs(this->config_file_.c_str());
        if (!ifs)
        {
            std::cerr << "can not open config file" << std::endl;
        }
        else
        {
            po::store(po::parse_config_file(ifs, this->opts_), this->variables_map_);
            notify(this->variables_map_);
        }
    }

} //end namespace parameters