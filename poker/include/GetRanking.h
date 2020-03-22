#pragma once

#include "Hand.h"

namespace poker{

    class GetRanking{
        
        public:

            bool isAceLowStreet(Hand& hand);

            GetRanking() {};
            ~GetRanking() {};

            // Using default copy and move constructors. 
            GetRanking(const GetRanking& other) = default;	
            GetRanking& operator=(const GetRanking& other) = default;
            GetRanking(GetRanking&& other) noexcept = default;
            GetRanking& operator=(GetRanking&& other) noexcept = default;

    };

}// end namespace poker