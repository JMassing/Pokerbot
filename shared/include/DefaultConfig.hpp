#pragma once

#include <sstream>
#include <iomanip>

#include "ConfigFileHandler.hpp"

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
            int wb_temperature;
            int zoom;
            int image_width;
            int image_height;
            
            // detection parameters
            int live_threshold;            
            int binary_threshold;          
            int identification_threshold;  
            
            // poker simulation parameters
            int nr_sim_runs;
            int nr_opponents;

            // gui layout parameters
            bool show_cards;
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
