#include "ConfigFileHandler.hpp"


    ConfigFileHandler::ConfigFileHandler(): 
    config_file_(), 
    opts_("Default Config"), 
    variables_map_()
    {
        fs::path filename = fs::current_path() / ".." / "config.ini";
        this->config_file_ = filename.string();
        this->setOptions();
        this->parseFile();
    }

    void ConfigFileHandler::setOptions()
    {
        this->opts_.add_options()
            ("camera.device_id", po::value<int>())
            ("camera.auto_exposure", po::value<bool>())
            ("camera.auto_focus", po::value<bool>())
            ("camera.auto_wb", po::value<bool>())
            ("camera.exposure_time", po::value<int>())
            ("camera.brightness", po::value<int>())
            ("camera.focus", po::value<int>())
            ("camera.zoom", po::value<int>())
            ("camera.image_width", po::value<int>())
            ("camera.image_height", po::value<int>())
            ("detection.live_threshold", po::value<int>())
            ("detection.binary_threshold", po::value<int>())
            ("detection.identification_threshold", po::value<int>())
            ("poker.nr_sim_runs", po::value<int>())
            ("poker.nr_opponents", po::value<int>())
            ("layout.show_cards", po::value<bool>())
            ("layout.live_image_width", po::value<int>())
            ("layout.live_image_height", po::value<int>())
            ("layout.card_outline_r", po::value<double>())
            ("layout.card_outline_g", po::value<double>())
            ("layout.card_outline_b", po::value<double>())
            ("layout.card_image_height_percent", po::value<int>())
            ("layout.card_rank_suit_height_percent", po::value<int>())
            ;

    }

    void ConfigFileHandler::parseFile()
    {
        std::ifstream ifs(this->config_file_.c_str());
        if (!ifs)
        {
            std::cerr << "can not open config file" << std::endl;
        }
        else
        {
            po::store(po::parse_config_file(ifs, this->opts_), this->variables_map_);
            notify(this->variables_map_);
            ifs.close();
        }
    }

     void ConfigFileHandler::writeFile(std::stringstream& file_content)
    {
        std::ofstream ofs(this->config_file_.c_str());
        if (!ofs)
        {
            std::cerr << "can not open config file" << std::endl;
        }
        else
        {
            ofs << file_content.str();
            ofs.close();
        }
    }

