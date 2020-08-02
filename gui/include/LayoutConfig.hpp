#pragma once

#include <opencv2/core.hpp>

#include "DefaultConfig.hpp"

namespace gui {

    struct LayoutConfig
    {
        bool show_cards;
        int live_view_height; 
        int live_view_width;
        int card_image_height_percent;
        int card_rank_suit_height_percent;
        cv::Scalar card_outline_color; 

        // Game Layout
        bool mask_robot_cards;
        bool show_probability;
        bool show_robot_hand;

        
		void setToDefault(const DefaultConfig& default_settings)
		{
            this->show_cards = default_settings.show_cards;
            this->live_view_height = default_settings.live_image_height;
            this->live_view_width = default_settings.live_image_width;
            this->card_image_height_percent = default_settings.card_image_height_percent;
            this->card_rank_suit_height_percent = default_settings.card_rank_suit_height_percent;
            this->card_outline_color = 
                {
                    default_settings.card_outline_b, 
                    default_settings.card_outline_g, 
                    default_settings.card_outline_r
                };
        }

        LayoutConfig():
            show_cards{false},
            live_view_height{720},
            live_view_width{1280},
            card_image_height_percent{100},
            card_rank_suit_height_percent{100},
            card_outline_color{0,0,0},
            mask_robot_cards{false},
            show_probability{true},
            show_robot_hand{true}
        { };
        ~LayoutConfig(){};

        // Using default copy and move constructors. 
        LayoutConfig(const LayoutConfig& other) = default;	
        LayoutConfig& operator=(const LayoutConfig& other) = default;
        LayoutConfig(LayoutConfig&& other) noexcept = default;
        LayoutConfig& operator=(LayoutConfig&& other) noexcept = default;
    };
}//end namespace gui