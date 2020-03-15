#pragma once

#include <vector>
#include <algorithm>

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "Mapping.h"

namespace poker{
    
    class Game{
        private:
        std::vector<Hand> player_hands;
        int nr_of_players;

        public:
        explicit Game(int nr_of_players);
        ~Game();

        std::vector<Hand> getHands() {return this->player_hands;}    
        void sortHands();

        // Using default copy and move constructors. 
        Game(const Game& other) = default;
        Game& operator=(const Game& other) = default;
        Game(Game&& other) noexcept = default;
        Game& operator=(Game&& other) noexcept = default;
    };

}//end namespace poker