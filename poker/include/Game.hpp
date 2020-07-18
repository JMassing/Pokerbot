#pragma once

#include <vector>
#include <memory>
#include <iostream>

#include "Simulation.hpp"
#include "SimSettings.hpp"
#include "DataPoker.hpp"
#include "IPokerGui.hpp"
#include "IPokerDetect.hpp"

// Coordinates the entities needed to run a monte carlo simulation with the given cards
namespace poker{
    
    class Game{
        
        private: 

            Simulation sim_;
            std::shared_ptr<IPokerGui> gui_interface_;
            std::shared_ptr<IPokerDetect> detect_interface_; 

        public:

            DataPoker data_;        

            void attachGuiInterface(std::shared_ptr<IPokerGui> interface)
			{
				this->gui_interface_ = interface;
			}

            void attachDetectInterface(std::shared_ptr<IPokerDetect> interface)
			{
				this->detect_interface_ = interface;
			}
            
            void play();

            Game(
                SimSettings settings,  
                const bool& log_sim = false
                ): 
                sim_(settings, log_sim),
                data_(),
                gui_interface_(nullptr),
                detect_interface_(nullptr)
            {};
            ~Game() {};   
                
            // Using default copy and move constructors. 
            Game(const Game& other) = default;
            Game& operator=(const Game& other) = default;
            Game(Game&& other) noexcept = default;
            Game& operator=(Game&& other) noexcept = default;        

    };

}//end namespace poker