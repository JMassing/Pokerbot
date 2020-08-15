#pragma once

#include "Hand.hpp"

namespace poker{

    const enum decision { NO_DECISION, CHECK, CALL, RAISE, HAS_RAISED, FOLD };

    struct Player
    {
            Hand hand;
            int money;                      // overall money the player is
            int money_in_play;              // overall money the player has in play
            int money_bet_in_phase;         // money the player has put in for this phase of betting
            int current_bet;
            int current_decision;
            bool has_folded;

            Player():
                hand{},
                money(0),
                money_bet_in_phase(0),
                money_in_play(0),
                current_bet(0),
                current_decision(NO_DECISION),
                has_folded(false)
            {}

            explicit Player(const int& starting_money):
                hand{},
                money(starting_money),
                money_bet_in_phase(0),
                money_in_play(0),
                current_bet(0),
                current_decision(NO_DECISION),
                has_folded(false)
            {}
            ~Player() {};
           
            // Using default copy and move constructors. 
            Player(const Player& other) = default;	
            Player& operator=(const Player& other) = default;
            Player(Player&& other) noexcept = default;
            Player& operator=(Player&& other) noexcept = default;
    };


}// end namespace poker