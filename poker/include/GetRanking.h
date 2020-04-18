#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include "Hand.h"
#include "BaseCard.h"
#include "Mapping.h"

namespace poker{

    class GetRanking{
        
        private:

            int ranking_;
            // the 5 highest card in the hand. Starting with the highest card and then decreaseing.
            // If you have a pair, the first two cards will be the cards of the pair and then the next highest card
            // If you have a straight, all five cards will be the highest card of the straight, since it is the only one that counds. Etc. ...
            std::array<int,5> high_cards_;

            void isMultipleOfCards(Hand& hand);   
            void isStraight(Hand& hand);
            bool isAceLowStreet(Hand& hand);
            Hand isFlush(Hand& hand);                        

        public:
             // Checks Ranks
            void run(Hand& hand);
            int getRanking(){return this->ranking_;};
            std::array<int,5> getHighCards(){return this->high_cards_;};
            void clear()
            {
                this->ranking_=-1;
                this->high_cards_.fill(0);
            }
            GetRanking():ranking_{-1}, high_cards_{-1} {};
            ~GetRanking() {};

            // Using default copy and move constructors. 
            GetRanking(const GetRanking& other) = default;	
            GetRanking& operator=(const GetRanking& other) = default;
            GetRanking(GetRanking&& other) noexcept = default;
            GetRanking& operator=(GetRanking&& other) noexcept = default;

    };

}// end namespace poker