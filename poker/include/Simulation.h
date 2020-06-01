#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <utility>

#include "Hand.h"
#include "Deck.h"
#include "BaseCard.h"
#include "Mapping.h"
#include "GetRanking.h"
#include "DataPokerGui.h"
#include "DataPokerDetect.h"


namespace poker{
    
    class Simulation{
        
        protected: //this is protected for unit testing purposes

            std::vector<Hand> player_hands_;
            std::shared_ptr<data::DataPokerGui> data_gui_;
            std::shared_ptr<data::DataPokerDetect> data_detect_;
            Hand robot_hand_;
            bool log_sim_;

            void updateHands(const std::vector<detect::BaseCard>& public_cards, const std::vector<detect::BaseCard>& robot_cards);
            void determineHandRankings();
            int  determineWinner();
            void logRun(const int& winner);

        public:

            void run();
            
            Simulation(std::shared_ptr<data::DataPokerGui>& data_gui, std::shared_ptr<data::DataPokerDetect>& data_detect, const bool& log_sim=false): data_gui_(data_gui), 
                data_detect_(data_detect), robot_hand_(), log_sim_{log_sim} 
            {
                this->player_hands_.resize(this->data_gui_->nr_of_human_players, Hand());
            };
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker