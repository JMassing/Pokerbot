#pragma once

#include "Hand.hpp"

namespace poker{

    enum decision { NO_DECISION, CHECK, CALL, RAISE, HAS_RAISED, FOLD };

    /**  \ingroup poker
	 * @class Player
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Data structure representing a player. Tracking the player hand, money, decision, bet and bet size.      
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    struct Player
    {
            Hand hand;
            /**
             * @brief Overall money the player has
             * 
             */
            int money;   
            /**
             * @brief Overall money the player has in play
             * 
             */
            int money_in_play;   
            /**
             * @brief Money the player has put in for this phase of betting
             * 
             */
            int money_bet_in_phase;   
            /**
             * @brief Money the player has bet in this round.
             * 
             */
            int current_bet;
            /**
             * @brief Player deicision
             * 
             */
            int current_decision;
            bool has_folded;
            bool is_all_in;

            Player():
                hand{},
                money(0),
                money_bet_in_phase(0),
                money_in_play(0),
                current_bet(0),
                current_decision(NO_DECISION),
                has_folded(false),
                is_all_in(false)
            {}

            explicit Player(const int& starting_money):
                hand{},
                money(starting_money),
                money_bet_in_phase(0),
                money_in_play(0),
                current_bet(0),
                current_decision(NO_DECISION),
                has_folded(false),
                is_all_in(false)
            {}
            ~Player() {};
           
            // Using default copy and move constructors. 
            Player(const Player& other) = default;	
            Player& operator=(const Player& other) = default;
            Player(Player&& other) noexcept = default;
            Player& operator=(Player&& other) noexcept = default;
    };


}// end namespace poker