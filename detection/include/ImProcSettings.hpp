#pragma once

#include "DefaultConfig.hpp"

namespace detect
{
    struct ImProcSettings
    {

        int live_threshold;            // threshold for finding cards in live image 
        int binary_threshold;          // threshold for binaryzing suit and rank image;
        int identification_threshold;  // threshold for finding the rank and suit in the card image 

        void setToDefault(DefaultConfig& default_settings)
        {
            this->live_threshold = default_settings.live_threshold;
            this->binary_threshold = default_settings.binary_threshold;
            this->identification_threshold = default_settings.identification_threshold;
        }

        ImProcSettings(): 
            live_threshold(120), 
            binary_threshold(120), 
            identification_threshold(120)
        {};
        
		~ImProcSettings(){};

		// Using default copy and move constructors. 
		ImProcSettings(const ImProcSettings& other) = default;	
		ImProcSettings& operator=(const ImProcSettings& other) = default;
		ImProcSettings(ImProcSettings&& other) noexcept = default;
		ImProcSettings& operator=(ImProcSettings&& other) noexcept = default;
    };
}// end namespace signals