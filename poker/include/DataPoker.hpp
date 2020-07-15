#pragma once

#include <utility>
#include <vector>

#include "Hand.hpp"

namespace poker
{
    struct DataPoker
    {

        std::vector<Hand> player_hands;
        Hand robot_hand;
        std::pair<double,double> probability;


        DataPoker(): player_hands(), robot_hand(), probability() {};
		~DataPoker(){};

		// Using default copy and move constructors. 
		DataPoker(const DataPoker& other) = default;	
		DataPoker& operator=(const DataPoker& other) = default;
		DataPoker(DataPoker&& other) noexcept = default;
		DataPoker& operator=(DataPoker&& other) noexcept = default;
    };
}// end namespace signals