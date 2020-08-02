#pragma once

#include <vector>

#include "Player.hpp"
#include "GameSettings.hpp"
#include "DataPoker.hpp"
#include "HandBuilder.hpp"
#include "MonteCarlo.hpp"


// Coordinates the entities needed to run a monte carlo simulation with the given cards
namespace poker{
    
    class Simulation{
        
        private: 

            bool log_sim_;
            GameSettings settings_;

        public:

            void updateSettings(GameSettings& settings)
            {
                this->settings_ = settings;
            }

            void run(DataPoker& data);
            
            Simulation(
                GameSettings settings,  
                const bool& log_sim = false
                ): 
                log_sim_{log_sim}, 
                settings_(settings)
            {};
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker