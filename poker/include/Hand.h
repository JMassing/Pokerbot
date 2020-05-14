#pragma once

#include <array>
#include <sstream>
#include <algorithm>

#include "BaseCard.h"
#include "TemplateFunctions.h"
#include "Mapping.h"

namespace poker{

    class Hand{
        
        public:

            std::array<detect::BaseCard,7> hand_;
            std::array<int,5> high_cards_;
            int ranking_;

            void addToHand(const detect::BaseCard& card);
            bool containsCard(const detect::BaseCard& card);
            bool containsRank(const int& rank);
            bool containsSuit(const int& suit);
            void sort();
            void clear();

            Hand(): ranking_{}, high_cards_{0}
            {
                hand_.fill(detect::BaseCard());
            }
            ~Hand() {};

            std::stringstream print();
            
            // Using default copy and move constructors. 
            Hand(const Hand& other) = default;	
            Hand& operator=(const Hand& other) = default;
            Hand(Hand&& other) noexcept = default;
            Hand& operator=(Hand&& other) noexcept = default;

    };

}// end namespace poker