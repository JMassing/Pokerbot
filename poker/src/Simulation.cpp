#include "Simulation.hpp"

namespace poker{
  
    //@brief: Runs the simulation. Return value is a pair of probabilities. pair.first gives 
    //        the probability to outright win with the robot hand. pair.second gives the probability 
    //        for the robot to have the highest ranking hand but tie with another player 
    void Simulation::run(
        const std::vector<BaseCard>& robot_cards, 
        const std::vector<BaseCard>& public_cards,
        DataPoker& data
        )
    {
        this->robot_cards_ = robot_cards;
        this->public_cards_ = public_cards;

        // update player hands size according to nr. of human players received from gui
        data.player_hands.resize(this->settings_.nr_of_human_players, Hand());

        // revert hands to build hands from scratch
        for(auto& hand: data.player_hands)
        {
            hand.clear();
        }
        data.robot_hand.clear();

        // reset hands with known cards
        HandBuilder::buildHands(
            this->public_cards_, 
            this->robot_cards_,
            data.player_hands,
            data.robot_hand
        );    
        
        // Run MonteCarlo Simulation
        data.probability = MonteCarlo::run(
            this->settings_,
            Deck(data.robot_hand),
            this->public_cards_,
            this->robot_cards_,
            this->log_sim_
        );         

        this->robot_cards_.clear();
        this->public_cards_.clear();
    }

}// end namespace poker