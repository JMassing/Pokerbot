#pragma once

#include <sstream>
#include <iomanip>

#include "ConfigFileHandler.hpp"

namespace shared
{
    struct DefaultConfig
    {
        public:
            // camera parameters
            int device_ID;
            bool auto_exposure;
            bool auto_focus;
            bool auto_wb;
            int exposure_time;
            int brightness;
            int focus;
            int zoom;
            int image_width;
            int image_height;
            
            // detection parameters
            int live_threshold;            // threshold for finding cards in live image 
            int binary_threshold;          // threshold for binaryzing suit and rank image;
            int identification_threshold;  // threshold for finding the rank and suit in the card image
            double card_aspect_ratio;
            int card_width;
            int min_card_size;
            int max_card_size;
            double min_comparison_confidence;
            double zoom_width_ratio;
            double zoom_height_ratio;
            double max_rank_contour_ratio;
            int perspective_transform_offset;
            int rank_suit_zoom_offset;

            // poker simulation parameters
            int nr_sim_runs;

            // gui display parameters
            int max_exp_time;
            int min_exp_time;
            int max_focus;
            int min_focus;
            int max_brightness;
            int min_brightness;
            int max_live_th;
            int min_live_th;
            int max_bin_th;
            int min_bin_th;
            int max_ident_th;
            int min_ident_th;
            int max_sim_runs;
            int min_sim_runs;
            int max_players;
            int min_players;

            // gui layout parameters
            bool show_frame;
            bool show_cards;
            bool show_im_proc_settings_window;
            bool show_main_window;
            bool show_card_img;
            bool show_rank_img;
            bool show_suit_img;
            bool show_camera_control;
            bool show_layout_window;
            int live_image_width;
            int live_image_height;
            double card_outline_r;
            double card_outline_g;
            double card_outline_b;
            int card_image_height_percent;
            int card_rank_suit_height_percent;

            void readConfig();
            void saveConfig();

            DefaultConfig() 
            {
                this->readConfig();
            };
            ~DefaultConfig(){};

            // Using default copy and move constructors. 
            DefaultConfig(const DefaultConfig& other) = default;	
            DefaultConfig& operator=(const DefaultConfig& other) = default;
            DefaultConfig(DefaultConfig&& other) noexcept = default;
            DefaultConfig& operator=(DefaultConfig&& other) noexcept = default;

        private:

            std::stringstream generateFileContents();
    };
}// end namespace signals