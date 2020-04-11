#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "Mapping.h"
#include "GetRanking.h"


namespace poker{
    
    class Game{
        
        protected: //this is protected for unit testing purposes

        std::vector<Hand> player_hands_;
        Hand robot_hand_;
        int nr_of_players_;

        void updateHands(std::array<detect::Card,5> public_cards, std::array<detect::Card,2> robot_cards);
        void getHandRankings();
        int getWinner();

        public:
        explicit Game(int nr_of_players): nr_of_players_{nr_of_players}, robot_hand_() 
        {
            
            this->player_hands_.resize(nr_of_players, Hand());
        };
        ~Game() {};

        std::vector<Hand> getHands() {return this->player_hands_;}    
       
        
              
        // Using default copy and move constructors. 
        Game(const Game& other) = default;
        Game& operator=(const Game& other) = default;
        Game(Game&& other) noexcept = default;
        Game& operator=(Game&& other) noexcept = default;
    };

}//end namespace poker