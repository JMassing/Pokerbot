#pragma once

#include <vector>
#include <memory>

#include "Hand.hpp"
#include "Deck.hpp"
#include "SimSettings.hpp"
#include "DataPoker.hpp"
#include "HandBuilder.hpp"
#include "MonteCarlo.hpp"
#include "IPokerGui.hpp"
#include "IPokerDetect.hpp"

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
            std::shared_ptr<IPokerGui> gui_interface_;
            std::shared_ptr<IPokerDetect> detect_interface_; 

        public:

            DataPoker data_;

            void run();

            void updateCards(std::vector<BaseCard> robot_cards,  std::vector<BaseCard> public_cards)
            {
                this->robot_cards_ = robot_cards;
                this->public_cards_ = public_cards;
            }

            void attachGuiInterface(std::shared_ptr<IPokerGui> interface)
			{
				this->gui_interface_ = interface;
			}

            void attachDetectInterface(std::shared_ptr<IPokerDetect> interface)
			{
				this->detect_interface_ = interface;
			}
            
            Simulation(
                SimSettings settings,  
                const bool& log_sim = false
                ): 
                log_sim_{log_sim}, 
                settings_(settings),
                data_(),
                robot_cards_{},
                public_cards_{},
                gui_interface_(nullptr),
                detect_interface_(nullptr)
            {};
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker