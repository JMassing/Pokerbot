#pragma once

#include <opencv2/core.hpp>

#include "DefaultConfig.h"

namespace gui {

    struct LayoutWinConfig
    {
        bool show_cards;
        bool show_camera_control;
        bool show_im_proc_settings_window;
        bool show_card_images;
        bool show_rank_images;
        bool show_suit_images;
        int live_image_height; 
        int live_image_width;
        const int card_image_height = 150;
        const int card_rank_suit_height = 50;
        int card_image_height_percent;
        int card_rank_suit_height_percent;
        cv::Scalar card_outline_color; 

        LayoutWinConfig():
            show_cards{false}, show_camera_control{false}, show_im_proc_settings_window{false}, show_card_images{false}, show_rank_images{false}, show_suit_images{false},
            live_image_height{0}, live_image_width{0}, card_image_height_percent{0}, card_rank_suit_height_percent{0}, card_outline_color{0,0,0}
        {

        };
        ~LayoutWinConfig(){};

        // Using default copy and move constructors. 
        LayoutWinConfig(const LayoutWinConfig& other) = default;	
        LayoutWinConfig& operator=(const LayoutWinConfig& other) = default;
        LayoutWinConfig(LayoutWinConfig&& other) noexcept = default;
        LayoutWinConfig& operator=(LayoutWinConfig&& other) noexcept = default;
    };
}//end namespace gui