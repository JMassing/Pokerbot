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

        ImProcSettings(int live_threshold, int binary_threshold, int identification_threshold): 
            live_threshold(live_threshold), 
            binary_threshold(binary_threshold), 
            identification_threshold(identification_threshold)
        {};

        bool operator==(const ImProcSettings& other) const
		{
			return 
			(
                this->live_threshold == other.live_threshold &&
                this->binary_threshold == other.binary_threshold &&
                this->identification_threshold == other.identification_threshold
			);
		};

		bool operator!=(const ImProcSettings& other) const
		{
		    return 
			(
			    this->live_threshold != other.live_threshold &&
                this->binary_threshold != other.binary_threshold &&
                this->identification_threshold != other.identification_threshold
			);
		};

        
		~ImProcSettings(){};

		// Using default copy and move constructors. 
		ImProcSettings(const ImProcSettings& other) = default;	
		ImProcSettings& operator=(const ImProcSettings& other) = default;
		ImProcSettings(ImProcSettings&& other) noexcept = default;
		ImProcSettings& operator=(ImProcSettings&& other) noexcept = default;
    };
}// end namespace signals