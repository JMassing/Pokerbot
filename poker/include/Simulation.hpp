#pragma once

#include <vector>

#include "Hand.hpp"
#include "Deck.hpp"
#include "SimSettings.hpp"
#include "DataPoker.hpp"
#include "HandBuilder.hpp"
#include "MonteCarlo.hpp"


// Coordinates the entities needed to run a monte carlo simulation with the given cards
namespace poker{
    
    class Simulation{
        
        private: 

            std::vector<Hand> player_hands_;
            Hand robot_hand_;
            bool log_sim_;
            SimSettings settings_;
            std::vector<BaseCard> robot_cards_;
            std::vector<BaseCard> public_cards_;

        public:

            void updateSettings(SimSettings& settings)
            {
                this->settings_ = settings;
            }

            void run( 
                const std::vector<BaseCard>& robot_cards, 
                const std::vector<BaseCard>& public_cards,
                DataPoker& data
                );
            
            Simulation(
                SimSettings settings,  
                const bool& log_sim = false
                ): 
                log_sim_{log_sim}, 
                settings_(settings),
                robot_cards_{},
                public_cards_{}
            {};
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker