#pragma once

#include <vector>
#include <array>
#include <utility>
#include <iostream>
#include <fstream>

#include "Deck.hpp"
#include "DataPoker.hpp"
#include "HandBuilder.hpp"
#include "WinnerDeterminator.hpp"
#include "BaseCard.hpp"
#include "Player.hpp"

namespace poker{

    /**  \ingroup poker
	* @class MonteCarlo
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Monte Carlo simulation of a poker game       
	*
	* @version 1.0
	* @date 2020-11-22
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    class MonteCarlo{
        
        public:

            /**  
             * @brief Write results of a simulation to logifle
             * 
             * @param winner 
             * @param player_hands 
             * @param robot_hand 
             */
            static void logRun(const int& winner, std::vector<Hand> player_hands, Hand robot_hand);

            /**
             * @brief Run the simulation
             * 
             * @param iterations Nr. of iterations
             * @param deck 
             * @param players 
             * @param game_phase current game phase (pre flop, flop, etc.)
             * @param log_sim true if results should be logged
             * @return std::pair<double,double> probability of bot winning, probability of tie
             */
            static std::pair<double,double> run(
                const int& iterations,
                Deck deck,
                const std::vector<Player>& players,
                const int& game_phase,
                const bool& log_sim = false
                );
            
            MonteCarlo(){};
            ~MonteCarlo() {};   
                
            // Using default copy and move constructors. 
            MonteCarlo(const MonteCarlo& other) = default;
            MonteCarlo& operator=(const MonteCarlo& other) = default;
            MonteCarlo(MonteCarlo&& other) noexcept = default;
            MonteCarlo& operator=(MonteCarlo&& other) noexcept = default;        

    };

}//end namespace poker