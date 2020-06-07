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

        DataDetectGui(): live_threshold(140), binary_threshold(140), identification_threshold(140),
            robot_cards(), public_cards()
            {
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