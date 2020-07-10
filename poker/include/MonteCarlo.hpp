#pragma once

#include <vector>
#include <array>
#include <utility>
#include <iostream>
#include <fstream>

#include "Hand.hpp"
#include "Deck.hpp"
#include "HandBuilder.hpp"
#include "WinnerDeterminator.hpp"
#include "BaseCard.hpp"
#include "SimSettings.hpp"

namespace poker{
    
    class MonteCarlo{
        
        public:

            static void logRun(const int& winner, std::vector<Hand> player_hands, Hand robot_hand);

            static std::pair<double,double> run(
                SimSettings& settings,
                Deck deck,
                const std::vector<detect::BaseCard>& public_cards,
                const std::vector<detect::BaseCard>& robot_cards,
                const bool& log_sim
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