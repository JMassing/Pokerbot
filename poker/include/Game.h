#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "Mapping.h"

namespace poker{
    
    class Game{
        protected:
        std::vector<Hand> player_hands_;

        void sortHands();
        bool isAceLowStreet(Hand& hand);

        public:
        Game(std::vector<Hand> player_hands):player_hands_(player_hands) {};
        ~Game() {};

        std::vector<Hand> getHands() {return this->player_hands_;}    
        void updatePlayerHands(std::vector<Hand> player_hands);
              
        // Using default copy and move constructors. 
        Game(const Game& other) = default;
        Game& operator=(const Game& other) = default;
        Game(Game&& other) noexcept = default;
        Game& operator=(Game&& other) noexcept = default;
    };

}//end namespace poker