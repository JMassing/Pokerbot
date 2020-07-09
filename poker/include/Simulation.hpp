#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <memory>

#include "Hand.hpp"
#include "Deck.hpp"
#include "BaseCard.h"
#include "Mapping.hpp"
#include "HandBuilder.hpp"
#include "WinnerDeterminator.hpp"
#include "SimSettings.hpp"
#include "DataPoker.hpp"
#include "DataDetect.hpp"

namespace poker{
    
    class Simulation{
        
        protected: //this is protected for unit testing purposes

            std::vector<Hand> player_hands_;
            Hand robot_hand_;
            bool log_sim_;
            SimSettings& settings_;
            detect::DataDetect& detected_cards_;

            void logRun(const int& winner);

        public:

            DataPoker data_;

            void run();
            
            Simulation(
                SimSettings& settings, 
                detect::DataDetect& detected_cards, 
                const bool& log_sim=false
                ): 
                log_sim_{log_sim}, 
                settings_(settings),
                detected_cards_(detected_cards),
                data_()
            {};
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker