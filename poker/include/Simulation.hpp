#pragma once

#include <vector>

#include "Hand.hpp"
#include "Deck.hpp"
#include "SimSettings.hpp"
#include "DataPoker.hpp"
#include "DataDetect.hpp"
#include "HandBuilder.hpp"
#include "MonteCarlo.hpp"

namespace poker{
    
    class Simulation{
        
        protected: //this is protected for unit testing purposes

            std::vector<Hand> player_hands_;
            Hand robot_hand_;
            bool log_sim_;
            SimSettings& settings_;
            detect::DataDetect& detected_cards_;

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