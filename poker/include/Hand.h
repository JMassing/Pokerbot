#pragma once

#include <array>
#include <sstream>

#include "Card.h"
#include "Mapping.h"

namespace poker{

    class Hand{
        
        public:
            std::array<detect::Card,7> hand;

            Hand()
            {
                hand.fill(detect::Card());
            }
            ~Hand() {};

            void addToHand(const detect::Card& card);
            bool contains(const detect::Card& card);
            std::stringstream print();
            
            // Using default copy and move constructors. 
            Hand(const Hand& other) = default;	
            Hand& operator=(const Hand& other) = default;
            Hand(Hand&& other) noexcept = default;
            Hand& operator=(Hand&& other) noexcept = default;

    };

}// end namespace poker