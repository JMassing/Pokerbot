#pragma once

#include <vector>

#include "Hand.h"
#include "Card.h"
#include "Mapping.h"

namespace poker{

    class GetRanking{
        
        private:
            int ranking;

            bool isPair(Hand& hand);   
            bool isTwoPair(Hand& hand);
            bool isThreeOfAKind(Hand& hand);
            bool isStraight(Hand& hand);
            bool isAceLowStreet(Hand& hand);
            bool isFlush(Hand& hand);
            bool isFullHouse(Hand& hand);
            bool isFourOfAKind(Hand& hand);

            // we have to paths, starting from Flush we only have to check better hands than Flush, which makes it faster if we have a flush
            // if we don't have a Flush we check for straight. If we don't have straight we check for Pair and the remaining better hands than pair
            void FlushPath(Hand& hand);
            void PairPath(Hand& hand);
            // Checks Ranks
            void checkRank(Hand& hand);
               

        public:

            int getRank(Hand& hand){return this->ranking;};

            GetRanking():ranking{detect::HIGH_CARD} {};
            ~GetRanking() {};

            // Using default copy and move constructors. 
            GetRanking(const GetRanking& other) = default;	
            GetRanking& operator=(const GetRanking& other) = default;
            GetRanking(GetRanking&& other) noexcept = default;
            GetRanking& operator=(GetRanking&& other) noexcept = default;

    };

}// end namespace poker