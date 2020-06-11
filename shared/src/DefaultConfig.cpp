#include "DefaultConfig.h"

namespace shared
{
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
        this->image_width = handler.getConfig()["camera.image_width"].as<int>();
        this->image_height = handler.getConfig()["camera.image_height"].as<int>();
        
        // read detection parameters
        this->live_threshold = handler.getConfig()["detection.live_threshold"].as<int>();
        this->binary_threshold = handler.getConfig()["detection.binary_threshold"].as<int>();
        this->identification_threshold = handler.getConfig()["detection.identification_threshold"].as<int>();
        this->card_aspect_ratio = handler.getConfig()["detection.card_aspect_ratio"].as<double>();
        this->card_width = handler.getConfig()["detection.card_width"].as<int>();
        this->min_card_size = handler.getConfig()["detection.min_card_size"].as<int>();
        this->max_card_size = handler.getConfig()["detection.max_card_size"].as<int>();
        this->min_comparison_confidence = handler.getConfig()["detection.min_comparison_confidence"].as<double>();
        this->zoom_width_ratio = handler.getConfig()["detection.zoom_width_ratio"].as<double>();
        this->zoom_height_ratio = handler.getConfig()["detection.zoom_height_ratio"].as<double>();
        this->max_rank_contour_ratio = handler.getConfig()["detection.max_rank_contour_ratio"].as<double>();
        this->perspective_transform_offset = handler.getConfig()["detection.perspective_transform_offset"].as<int>();
        this->rank_suit_zoom_offset = handler.getConfig()["detection.rank_suit_zoom_offset"].as<int>();

        // read poker simulation parameters
        this->nr_sim_runs = handler.getConfig()["poker.nr_sim_runs"].as<int>();

        // read gui parameters
        this->max_exp_time = handler.getConfig()["gui.max_exp_time"].as<int>();
        this->min_exp_time = handler.getConfig()["gui.min_exp_time"].as<int>();
        this->max_focus = handler.getConfig()["gui.max_focus"].as<int>();
        this->min_focus = handler.getConfig()["gui.min_focus"].as<int>();
        this->max_brightness = handler.getConfig()["gui.max_brightness"].as<int>();
        this->min_brightness = handler.getConfig()["gui.min_brightness"].as<int>();
        this->max_live_th = handler.getConfig()["gui.max_live_th"].as<int>();
        this->min_live_th = handler.getConfig()["gui.min_live_th"].as<int>();
        this->max_bin_th = handler.getConfig()["gui.max_bin_th"].as<int>();
        this->min_bin_th = handler.getConfig()["gui.min_bin_th"].as<int>();
        this->max_ident_th = handler.getConfig()["gui.max_ident_th"].as<int>();
        this->min_ident_th = handler.getConfig()["gui.min_ident_th"].as<int>();
        this->max_sim_runs = handler.getConfig()["gui.max_sim_runs"].as<int>();
        this->min_sim_runs = handler.getConfig()["gui.min_sim_runs"].as<int>();
        this->max_players = handler.getConfig()["gui.max_players"].as<int>();
        this->min_players = handler.getConfig()["gui.min_players"].as<int>();

        // read gui layout parameters 
        this->show_frame = handler.getConfig()["layout.show_frame"].as<bool>();
        this->show_cards = handler.getConfig()["layout.show_cards"].as<bool>();
        this->show_im_proc_settings_window = handler.getConfig()["layout.show_im_proc_settings_window"].as<bool>();
        this->show_main_window = handler.getConfig()["layout.show_main_window"].as<bool>();
        this->show_card_img = handler.getConfig()["layout.show_card_img"].as<bool>();
        this->show_rank_img = handler.getConfig()["layout.show_rank_img"].as<bool>();
        this->show_suit_img = handler.getConfig()["layout.show_suit_img"].as<bool>();
        this->show_camera_control = handler.getConfig()["layout.show_camera_control"].as<bool>();
        this->show_layout_window = handler.getConfig()["layout.show_layout_window"].as<bool>();
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
        handler.writeFile(this->generateFileContents());
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
        << "image_width = " << this->image_width << "\n"
        << "image_height = " << this->image_height << "\n"

        << "\n[detection]\n"
        << "live_threshold = " << this->live_threshold << "\n" 
        << "binary_threshold = " << this->binary_threshold << "\n" 
        << "identification_threshold = " << this->identification_threshold << "\n"
        << "#Empirical parameters.\n"
        << "card_aspect_ratio = " << this->card_aspect_ratio << "\n"
        << "card_width = " << this->card_width << "\n"
        << "min_card_size = " << this->min_card_size << "\n"
        << "max_card_size = " << this->max_card_size << "\n"
        << "min_comparison_confidence = " << this->min_comparison_confidence << "\n"
        << "zoom_width_ratio = " << this->zoom_width_ratio << "\n"
        << "zoom_height_ratio = " << this->zoom_height_ratio << "\n"
        << "max_rank_contour_ratio = " << this->max_rank_contour_ratio << "\n"
        << "perspective_transform_offset = " << this->perspective_transform_offset << "\n"
        << "rank_suit_zoom_offset = " << this->rank_suit_zoom_offset << "\n"

        << "\n[poker]\n"
        << "nr_sim_runs = " << this->nr_sim_runs << "\n"

        << "\n[gui]\n"
        << "#camera\n"
        << "max_exp_time = " << this->max_exp_time << "\n"
        << "min_exp_time = " << this->min_exp_time << "\n"
        << "max_focus = " << this->max_focus << "\n"
        << "min_focus = " << this->min_focus << "\n"
        << "max_brightness = " << this->max_brightness << "\n"
        << "min_brightness = " << this->min_brightness << "\n"
        << "#detection\n"
        << "max_live_th = " << this->max_live_th << "\n"
        << "min_live_th = " << this->min_live_th << "\n"
        << "max_bin_th = " << this->max_bin_th  << "\n"
        << "min_bin_th = " << this->min_bin_th << "\n"
        << "max_ident_th = " << this->max_ident_th << "\n"
        << "min_ident_th = " << this->min_ident_th << "\n"
        << "#poker\n"
        << "max_sim_runs = " << this->max_sim_runs  << "\n"
        << "min_sim_runs = " << this->min_sim_runs  << "\n"
        << "max_players = " << this->max_players  << "\n"
        << "min_players = " << this->min_players << "\n"

        << "\n[layout]\n"
        << "show_frame = " << this->show_frame << "\n"
        << "show_cards = " << this->show_cards << "\n"
        << "show_im_proc_settings_window = " << this->show_im_proc_settings_window << "\n"
        << "show_main_window = " << this->show_main_window << "\n"
        << "show_card_img = " << this->show_card_img << "\n"
        << "show_rank_img = " << this->show_rank_img << "\n"
        << "show_suit_img = " << this->show_suit_img << "\n"
        << "show_camera_control = " << this->show_camera_control << "\n"
        << "show_layout_window = " << this->show_layout_window << "\n"
        << "live_image_width = " << this->live_image_width << "\n"
        << "live_image_height = " << this->live_image_height << "\n"
        << "card_outline_r = " << this->card_outline_r << "\n"
        << "card_outline_g = " << this->card_outline_g << "\n"
        << "card_outline_b = " << this->card_outline_b << "\n"
        << "card_image_height_percent = " << this->card_image_height_percent << "\n"
        << "card_rank_suit_height_percent = " << this->card_rank_suit_height_percent << "\n";

    return config;
        
    }

}