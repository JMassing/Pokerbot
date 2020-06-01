#pragma once

#include <vector>

#include <opencv2/core.hpp>

#include "Card.h"

namespace data
{
    struct DataDetectGui
    {

        std::vector<detect::Card> robot_cards;
        std::vector<detect::Card> public_cards;
        int live_threshold;            // threshold added to mean image intensity for finding cards in live image (cards are brighter than background, so +)
        int binary_threshold;          // threshold added to mean image intensity for binaryzing suit and rank image;
        int identification_threshold;  // threshold added to mean image intensity for finding the rank and suit in the card image (rank and suit are darker than card image, so -)
        cv::Rect robot_area;           // area where to place the robot cards in the image
        cv::Rect public_area;          // area where to place the public cards in the image

        DataDetectGui(): live_threshold(40), binary_threshold(0), identification_threshold(-10),
            robot_cards(), public_cards() 
            {
                robot_area.x = 350;
                robot_area.y = 620;
                robot_area.width = 1150;
                robot_area.height = 2800;

                public_area.x = 50;
                public_area.y = 300;
                public_area.width = 1450;
                public_area.height = 310;
            };
		~DataDetectGui(){};

		// Using default copy and move constructors. 
		DataDetectGui(const DataDetectGui& other) = default;	
		DataDetectGui& operator=(const DataDetectGui& other) = default;
		DataDetectGui(DataDetectGui&& other) noexcept = default;
		DataDetectGui& operator=(DataDetectGui&& other) noexcept = default;
    };
}// end namespace signals