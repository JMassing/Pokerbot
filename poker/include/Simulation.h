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


namespace poker{
    
    class Simulation{
        
        protected: //this is protected for unit testing purposes

            std::vector<Hand> player_hands_;
            Hand robot_hand_;
            int nr_of_human_players_;
            int nr_of_iterations_;
            bool log_sim_;

            void updateHands(const std::vector<detect::BaseCard>& public_cards, const std::array<detect::BaseCard,2>& robot_cards);
            void determineHandRankings();
            int determineWinner();
            void logRun(const int& winner);

        public:

            std::pair<double,double> run(const std::vector<detect::BaseCard>& public_cards, const std::array<detect::BaseCard,2>& robot_cards);
            Simulation(int nr_of_human_players, int nr_of_iterations, bool log_sim=false): nr_of_human_players_{nr_of_human_players}, 
                nr_of_iterations_{nr_of_iterations}, robot_hand_(), log_sim_{log_sim} 
            {
                this->player_hands_.resize(nr_of_human_players, Hand());
            };
            ~Simulation() {};   
                
            // Using default copy and move constructors. 
            Simulation(const Simulation& other) = default;
            Simulation& operator=(const Simulation& other) = default;
            Simulation(Simulation&& other) noexcept = default;
            Simulation& operator=(Simulation&& other) noexcept = default;        

    };

}//end namespace poker