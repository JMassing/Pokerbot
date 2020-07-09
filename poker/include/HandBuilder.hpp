#pragma once

#include <vector>

#include "BaseCard.h"
#include "Hand.hpp"

namespace poker{

    class HandBuilder{
        
        public:

            static void buildHands(
                const std::vector<detect::BaseCard>& public_cards, 
                const std::vector<detect::BaseCard>& robot_cards,
                std::vector<Hand>& player_hands,
                Hand& robot_hand
                );

            HandBuilder() {};
            ~HandBuilder() {};
            
            // Using default copy and move constructors. 
            HandBuilder(const HandBuilder& other) = default;	
            HandBuilder& operator=(const HandBuilder& other) = default;
            HandBuilder(HandBuilder&& other) noexcept = default;
            HandBuilder& operator=(HandBuilder&& other) noexcept = default;

    };

}// end namespace poker