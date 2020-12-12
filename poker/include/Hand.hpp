#pragma once

#include <array>
#include <sstream>
#include <algorithm>

#include "BaseCard.hpp"
#include "TemplateFunctions.hpp"
#include "Mapping.hpp"

namespace poker{

    /**  \ingroup poker
	 * @class Hand
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Object representing a players hand.        
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class Hand{
        
        public:

            std::array<BaseCard,7> cards_;
            std::array<int,5> high_cards_;
            int ranking_;

            void addToHand(const BaseCard& card);
            bool containsCard(const BaseCard& card);
            bool containsRank(const int& rank);
            bool containsSuit(const int& suit);
            void sort();
            void reset();

            Hand(): ranking_{}, high_cards_{0}
            {
                cards_.fill(BaseCard(UNKNOWN, UNKNOWN));
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