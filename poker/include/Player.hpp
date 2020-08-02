#pragma once

#include "Hand.hpp"

namespace poker{

    const enum decision { NO_DECISION, FOLD, CALL, RAISE };

    struct Player
    {
            Hand hand;
            int money;
            int current_bet;
            int current_decision;

            Player():
                hand{},
                money(0),
                current_bet(0),
                current_decision(NO_DECISION)
            {}

            explicit Player(const int& starting_money):
                hand{},
                money(starting_money),
                current_bet(0),
                current_decision(NO_DECISION)
            {}
            ~Player() {};
           
            // Using default copy and move constructors. 
            Player(const Player& other) = default;	
            Player& operator=(const Player& other) = default;
            Player(Player&& other) noexcept = default;
            Player& operator=(Player&& other) noexcept = default;
    };


}// end namespace poker