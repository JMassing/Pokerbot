#pragma once

#include <utility>

#include <opencv2/core.hpp>

#include "BaseCard.h"

namespace data
{
    struct DataPokerDetect
    {

        std::vector<detect::BaseCard> public_cards;
        std::vector<detect::BaseCard> robot_cards;

        DataPokerDetect(): public_cards(), robot_cards() {};
		~DataPokerDetect(){};

		// Using default copy and move constructors. 
		DataPokerDetect(const DataPokerDetect& other) = default;	
		DataPokerDetect& operator=(const DataPokerDetect& other) = default;
		DataPokerDetect(DataPokerDetect&& other) noexcept = default;
		DataPokerDetect& operator=(DataPokerDetect&& other) noexcept = default;
    };
}// end namespace signals