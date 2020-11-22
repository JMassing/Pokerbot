#pragma once

#include <utility>
#include <vector>

#include "Player.hpp"
#include "BaseCard.hpp"

namespace poker
{
    enum phase { NOT_STARTED, HAND_CARDS, BET_HAND, FLOP, BET_FLOP, TURN, BET_TURN, RIVER, BET_RIVER, SHOW_DOWN };

	/** \ingroup poker
	* @class DataPoker
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Data structure containing poker module output data to GUI module
	*
	* @version 1.0
	* @date 2020-11-18
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    struct DataPoker
    {

        std::vector<Player> players;
        std::pair<double,double> probability;
        int game_phase;
        int whos_turn;
        int button_pos;
        int highest_bet;
        int winner;
        int pot_size;
        bool next_round;
        std::vector<BaseCard> robot_cards; 

    	void nextPlayer()
        {
            this->whos_turn = (this->whos_turn + 1) % this->players.size();
        }

        DataPoker(): 
            players(), 
            probability(), 
            game_phase(0), 
            whos_turn(0),
            highest_bet(0),
            winner(-2),
            pot_size(0),
            next_round(false)
        {};
		~DataPoker(){};

		// Using default copy and move constructors. 
		DataPoker(const DataPoker& other) = default;	
		DataPoker& operator=(const DataPoker& other) = default;
		DataPoker(DataPoker&& other) noexcept = default;
		DataPoker& operator=(DataPoker&& other) noexcept = default;
    };
}// end namespace signals