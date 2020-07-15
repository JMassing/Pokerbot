#pragma once

#include <vector>

#include "BaseCard.hpp"
#include "Hand.hpp"

// Builds the robot and player hands out of given robot cards and
// public card from detection module
namespace poker{

    class HandBuilder{
        
        public:

            static void buildHands(
                const std::vector<BaseCard>& public_cards, 
                const std::vector<BaseCard>& robot_cards,
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