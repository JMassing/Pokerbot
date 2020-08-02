#pragma once

#include <utility>
#include <vector>

#include "Player.hpp"

namespace poker
{
    const enum phase { NOT_STARTED, HAND_CARDS, FLOP, TURN, RIVER, PLACE_BETS };

    struct DataPoker
    {

        std::vector<Player> players;
        std::pair<double,double> probability;
        int game_phase;
        int whos_turn;
        int button_pos;
        std::vector<Hand> player_hands;
        Hand robot_hand;
        std::vector<int> player_money;


        DataPoker(): 
            players(), 
            probability(), 
            game_phase(0), 
            whos_turn(0),
            player_hands(),
            robot_hand(),
            player_money()
        {};
		~DataPoker(){};

		// Using default copy and move constructors. 
		DataPoker(const DataPoker& other) = default;	
		DataPoker& operator=(const DataPoker& other) = default;
		DataPoker(DataPoker&& other) noexcept = default;
		DataPoker& operator=(DataPoker&& other) noexcept = default;
    };
}// end namespace signals