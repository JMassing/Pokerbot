#pragma once

#include <array>
#include <sstream>

#include "Card.h"
#include "Mapping.h"

namespace poker{

    class Hand{
        
        public:

            std::array<detect::Card,7> hand_;
            std::array<int,5> high_cards_;
            int ranking_;

            Hand(): ranking_{}, high_cards_{0}
            {
                hand_.fill(detect::Card());
            }
            ~Hand() {};

            void addToHand(const detect::Card& card);
            bool containsCard(const detect::Card& card);
            bool containsRank(const int& rank);
            bool containsSuit(const int& suit);
            void sort();

            std::stringstream print();
            
            // Using default copy and move constructors. 
            Hand(const Hand& other) = default;	
            Hand& operator=(const Hand& other) = default;
            Hand(Hand&& other) noexcept = default;
            Hand& operator=(Hand&& other) noexcept = default;

    };

}// end namespace poker