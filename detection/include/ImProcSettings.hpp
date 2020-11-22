#pragma once

#include "DefaultConfig.hpp"

namespace detect
{
    /** *\ingroup detection
	* @class ImProcSettings
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Data structure containing image processing settings
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    struct ImProcSettings
    {
        /**
         * @brief threshold for finding cards in live image
         * 
         */
        int live_threshold;            
        /**
         * @brief threshold for binaryzing suit and rank image
         * 
         */
        int binary_threshold;          
        /**
         * @brief threshold for finding the rank and suit in the card image
         * 
         */
        int identification_threshold; 

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