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

// Monte Carlo simulation of poker game
namespace poker{
    
    class MonteCarlo{
        
        public:

            static void logRun(const int& winner, std::vector<Hand> player_hands, Hand robot_hand);

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