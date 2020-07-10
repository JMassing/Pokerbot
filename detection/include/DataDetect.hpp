#pragma once

// Data Structure holding output data to poker module

#include <utility>
#include <vector>

#include "BaseCard.hpp"

namespace detect
{
    struct DataDetect
    {

        std::vector<BaseCard> public_cards;
        std::vector<BaseCard> robot_cards;

        DataDetect(): public_cards(), robot_cards() {};
		~DataDetect(){};

		// Using default copy and move constructors. 
		DataDetect(const DataDetect& other) = default;	
		DataDetect& operator=(const DataDetect& other) = default;
		DataDetect(DataDetect&& other) noexcept = default;
		DataDetect& operator=(DataDetect&& other) noexcept = default;
    };
}// end namespace signals