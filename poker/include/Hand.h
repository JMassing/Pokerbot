#pragma once

#include<array>
#include <sstream>


#include "Card.h"
#include "Mapping.h"

namespace poker{

    struct Hand{

        std::array<detect::Card,5> hand;

        Hand()
        {
            hand.fill(detect::Card());
        }
        ~Hand() {};

        void addToHand(const detect::Card& card);
        std::stringstream print();
        // Using default copy and move constructors. 
		Hand(const Hand& other) = default;	
		Hand& operator=(const Hand& other) = default;
		Hand(Hand&& other) noexcept = default;
		Hand& operator=(Hand&& other) noexcept = default;

        private:
        bool contains(const detect::Card& card);

    };

}// end namespace poker