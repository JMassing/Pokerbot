#pragma once

#include <opencv2/core.hpp>

namespace gui {

    struct LayoutConfig
    {
        bool show_cards;
        bool show_camera_control;
        bool show_im_proc_settings_window;
        bool show_card_images;
        bool show_rank_images;
        bool show_suit_images;
        int live_image_height; 
        int live_image_width;
        int card_image_height_percent;
        int card_rank_suit_height_percent;
        cv::Scalar card_outline_color; 

        LayoutConfig():
            show_cards{false}, show_camera_control{false}, show_im_proc_settings_window{false}, show_card_images{false}, show_rank_images{false}, show_suit_images{false},
            live_image_height{720}, live_image_width{1280}, card_image_height_percent{100}, card_rank_suit_height_percent{100}, card_outline_color{0,0,0}
        { };
        ~LayoutConfig(){};

        // Using default copy and move constructors. 
        LayoutConfig(const LayoutConfig& other) = default;	
        LayoutConfig& operator=(const LayoutConfig& other) = default;
        LayoutConfig(LayoutConfig&& other) noexcept = default;
        LayoutConfig& operator=(LayoutConfig&& other) noexcept = default;
    };
}//end namespace gui