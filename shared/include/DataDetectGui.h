#pragma once

#include <vector>
#include <memory>

#include <opencv2/core.hpp>

#include "Card.h"
#include "DefaultConfig.h"

namespace shared
{
    struct DataDetectGui
    {

        std::vector<detect::Card> robot_cards;
        std::vector<detect::Card> public_cards;       
        int live_threshold;            // threshold for finding cards in live image 
        int binary_threshold;          // threshold for binaryzing suit and rank image;
        int identification_threshold;  // threshold for finding the rank and suit in the card image 
        cv::Rect robot_area;           // area where to place the robot cards in the image
        cv::Rect public_area;          // area where to place the public cards in the image
        std::shared_ptr<DefaultConfig> default_config;

        void setToDefault()
		{
			this->live_threshold = default_config->live_threshold;
            this->binary_threshold = default_config->binary_threshold;
            this->identification_threshold = default_config->identification_threshold;
		}

        void saveAsDefault()
		{
            default_config->live_threshold = this->live_threshold;
            default_config->binary_threshold = this->binary_threshold;
            default_config->identification_threshold = this->identification_threshold;
            this->default_config->saveConfig();
		}

        DataDetectGui(std::shared_ptr<DefaultConfig> default_config): default_config(default_config), robot_cards(), public_cards()
        {
            this->setToDefault();
            robot_area.x = 160;
            robot_area.y = 260;
            robot_area.width = 320;
            robot_area.height = 200;

            public_area.x = 10;
            public_area.y = 100;
            public_area.width = 620;
            public_area.height = 150;

            // reserve space for robot and public cards, should be max of 2 robot and 5 public cards
            robot_cards.reserve(2);
            public_cards.reserve(5);
         };
		~DataDetectGui(){};

		// Using default copy and move constructors. 
		DataDetectGui(const DataDetectGui& other) = default;	
		DataDetectGui& operator=(const DataDetectGui& other) = default;
		DataDetectGui(DataDetectGui&& other) noexcept = default;
		DataDetectGui& operator=(DataDetectGui&& other) noexcept = default;
    };
}// end namespace signals