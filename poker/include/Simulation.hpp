#pragma once

#include <vector>
#include <memory>

#include "Hand.hpp"
#include "Deck.hpp"
#include "SimSettings.hpp"
#include "DataPoker.hpp"
#include "DataDetect.hpp"
#include "HandBuilder.hpp"
#include "MonteCarlo.hpp"
#include "IPokerGui.hpp"
#include "IPokerDetect.hpp"

namespace poker{
    
    class Simulation{
        
        protected: //this is protected for unit testing purposes

            std::vector<Hand> player_hands_;
            Hand robot_hand_;
            bool log_sim_;
            SimSettings settings_;
            detect::DataDetect detected_cards_;
            std::shared_ptr<IPokerGui> gui_io_;
            std::shared_ptr<IPokerDetect> detect_in_; 

        public:

            DataPoker data_;

            void run();

            void updateCards(detect::DataDetect detected_cards)
            {
                this->detected_cards_ = detected_cards;
            }

            void attachGuiInterface(std::shared_ptr<IPokerGui> interface)
			{
				this->gui_io_ = interface;
			}

            void attachDetectInterface(std::shared_ptr<IPokerDetect> interface)
			{
				this->detect_in_ = interface;
			}
            
            Simulation(
                SimSettings settings,  
                const bool& log_sim = false
                ): 
                log_sim_{log_sim}, 
                settings_(settings),
                detected_cards_{},
                data_(),
                gui_io_(nullptr),
                detect_in_(nullptr)
            {};
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker