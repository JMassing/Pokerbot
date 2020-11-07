#include "DefaultConfig.hpp"

    void DefaultConfig::readConfig()
    {
        ConfigFileHandler handler{};
        
        //read camera parameters
        this->device_ID = handler.getConfig()["camera.device_id"].as<int>();
        this->auto_exposure = handler.getConfig()["camera.auto_exposure"].as<bool>();
        this->auto_focus = handler.getConfig()["camera.auto_focus"].as<bool>();
        this->auto_wb = handler.getConfig()["camera.auto_wb"].as<bool>();
        this->exposure_time = handler.getConfig()["camera.exposure_time"].as<int>();
        this->brightness = handler.getConfig()["camera.brightness"].as<int>();
        this->focus = handler.getConfig()["camera.focus"].as<int>();
        this->zoom = handler.getConfig()["camera.zoom"].as<int>();
        this->wb_temperature = handler.getConfig()["camera.wb_temperature"].as<int>();
        this->image_width = handler.getConfig()["camera.image_width"].as<int>();
        this->image_height = handler.getConfig()["camera.image_height"].as<int>();
        
        // read detection parameters
        this->live_threshold = handler.getConfig()["detection.live_threshold"].as<int>();
        this->binary_threshold = handler.getConfig()["detection.binary_threshold"].as<int>();
        this->identification_threshold = handler.getConfig()["detection.identification_threshold"].as<int>();
       
        // read poker simulation parameters
        this->nr_sim_runs = handler.getConfig()["poker.nr_sim_runs"].as<int>();
        this->nr_opponents = handler.getConfig()["poker.nr_opponents"].as<int>();

        // read gui layout parameters 
        this->show_cards = handler.getConfig()["layout.show_cards"].as<bool>();
        this->live_image_width = handler.getConfig()["layout.live_image_width"].as<int>();
        this->live_image_height = handler.getConfig()["layout.live_image_height"].as<int>();
        this->card_outline_r = handler.getConfig()["layout.card_outline_r"].as<double>();
        this->card_outline_g = handler.getConfig()["layout.card_outline_g"].as<double>();
        this->card_outline_b = handler.getConfig()["layout.card_outline_b"].as<double>();
        this->card_image_height_percent = handler.getConfig()["layout.card_image_height_percent"].as<int>();
        this->card_rank_suit_height_percent = handler.getConfig()["layout.card_rank_suit_height_percent"].as<int>();

    }

    void DefaultConfig::saveConfig()
    {
        ConfigFileHandler handler{};
        std::stringstream config = this->generateFileContents();
        handler.writeFile(config);
    }

    std::stringstream DefaultConfig::generateFileContents()
    {
        std::stringstream config;

        config << std::boolalpha
        << "[camera]\n"
        << "device_id = " << this->device_ID << "\n"
        << "auto_exposure = " << this->auto_exposure << "\n"
        << "auto_focus = " << this->auto_focus << "\n"
        << "auto_wb = " << this->auto_wb << "\n"
        << "exposure_time = " << this->exposure_time << "\n"
        << "brightness = " << this->brightness << "\n"
        << "focus = " << this->focus << "\n"
        << "zoom = " << this->zoom << "\n"
        << "wb_temperature = " << this->wb_temperature << "\n"
        << "image_width = " << this->image_width << "\n"
        << "image_height = " << this->image_height << "\n"

        << "\n[detection]\n"
        << "live_threshold = " << this->live_threshold << "\n" 
        << "binary_threshold = " << this->binary_threshold << "\n" 
        << "identification_threshold = " << this->identification_threshold << "\n"
        
        << "\n[poker]\n"
        << "nr_sim_runs = " << this->nr_sim_runs << "\n"
        << "nr_opponents = " << this->nr_opponents << "\n"

        << "\n[layout]\n"
        << "show_cards = " << this->show_cards << "\n"
        << "live_image_width = " << this->live_image_width << "\n"
        << "live_image_height = " << this->live_image_height << "\n"
        << "card_outline_r = " << this->card_outline_r << "\n"
        << "card_outline_g = " << this->card_outline_g << "\n"
        << "card_outline_b = " << this->card_outline_b << "\n"
        << "card_image_height_percent = " << this->card_image_height_percent << "\n"
        << "card_rank_suit_height_percent = " << this->card_rank_suit_height_percent << "\n";

    return config;
        
    }

