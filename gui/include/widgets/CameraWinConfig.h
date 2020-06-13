#pragma once

namespace gui {

    struct CameraWinConfig
    {
        int device_id;
        bool auto_exposure;
        bool auto_focus;
        bool auto_wb;
        int exposure_time;
        int brightness;
        int focus;
        int zoom;
        int image_width;
        int image_height;
        int max_exp_time;
        int min_exp_time;
        int max_focus;
        int min_focus;
        int max_brightness;
        int min_brightness;

        CameraWinConfig(): 
        device_id(0), auto_exposure(true), auto_focus(true), auto_wb(true), exposure_time(-5), brightness(128), focus(40), zoom(100), 
        image_width(1280), image_height(720), max_exp_time(-1), min_exp_time(-12), max_focus(250), min_focus(0), max_brightness(255),
        min_brightness(0) {};
        ~CameraWinConfig(){};

        // Using default copy and move constructors. 
        CameraWinConfig(const CameraWinConfig& other) = default;	
        CameraWinConfig& operator=(const CameraWinConfig& other) = default;
        CameraWinConfig(CameraWinConfig&& other) noexcept = default;
        CameraWinConfig& operator=(CameraWinConfig&& other) noexcept = default;
    };
}//end namespace gui