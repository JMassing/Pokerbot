#include "ConfigFileHandler.h"

namespace shared
{

    ConfigFileHandler::ConfigFileHandler(): config_file_("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot_build\\bin\\config.ini"), opts_("Default Config"), variables_map_()
    {
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
            ("detection.card_aspect_ratio", po::value<double>())
            ("detection.card_width", po::value<int>())
            ("detection.min_card_size", po::value<int>())
            ("detection.max_card_size", po::value<int>())
            ("detection.min_comparison_confidence", po::value<double>())
            ("detection.zoom_width_ratio", po::value<double>())
            ("detection.zoom_height_ratio", po::value<double>())
            ("detection.max_rank_contour_ratio", po::value<double>())
            ("detection.perspective_transform_offset", po::value<int>())
            ("detection.rank_suit_zoom_offset", po::value<int>())
            ("poker.nr_sim_runs", po::value<int>())
            ("gui.max_exp_time", po::value<int>())
            ("gui.min_exp_time", po::value<int>())
            ("gui.max_focus", po::value<int>())
            ("gui.min_focus", po::value<int>())
            ("gui.max_brightness", po::value<int>())
            ("gui.min_brightness", po::value<int>())
            ("gui.max_live_th", po::value<int>())
            ("gui.min_live_th", po::value<int>())
            ("gui.max_bin_th", po::value<int>())
            ("gui.min_bin_th", po::value<int>())
            ("gui.max_ident_th", po::value<int>())
            ("gui.min_ident_th", po::value<int>())
            ("gui.max_sim_runs", po::value<int>())
            ("gui.min_sim_runs", po::value<int>())
            ("gui.max_players", po::value<int>())
            ("gui.min_players", po::value<int>())
            ("layout.show_frame", po::value<bool>())
            ("layout.show_cards", po::value<bool>())
            ("layout.show_im_proc_settings_window", po::value<bool>())
            ("layout.show_main_window", po::value<bool>())
            ("layout.show_card_img", po::value<bool>())
            ("layout.show_rank_img", po::value<bool>())
            ("layout.show_suit_img", po::value<bool>())
            ("layout.show_camera_control", po::value<bool>())
            ("layout.show_layout_window", po::value<bool>())
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

} //end namespace parameters