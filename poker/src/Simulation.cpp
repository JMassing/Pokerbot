#include "Simulation.hpp"

#include <iostream>
#include <fstream>

namespace poker{
  
    //@brief: Runs the simulation. Return value is a pair of probabilities. pair.first gives 
    //        the probability to outright win with the robot hand. pair.second gives the probability 
    //        for the robot to have the highest ranking hand but tie with another player 
    void Simulation::run()
    {
         // get settings from GUI if a GUI is connected
		if(this->gui_interface_ != nullptr)
		{
			if(this->gui_interface_->checkUserInput())
			{
				this->settings_ = this->gui_interface_->getSettings();
			}
		}

        // get detected cards from detection module if connected
		if(this->detect_interface_ != nullptr)
		{
			this->updateCards(
                    detect_interface_->getData().robot_cards, 
                    detect_interface_->getData().public_cards
                );
		}

        // update player hands size according to nr. of human players received from gui
        this->data_.player_hands.resize(this->settings_.nr_of_human_players, Hand());

        // revert hands to build hands from scratch
        for(auto& hand: this->data_.player_hands)
        {
            hand.clear();
        }
        this->data_.robot_hand.clear();

        // reset hands with known cards
        HandBuilder::buildHands(
            this->public_cards_, 
            this->robot_cards_,
            this->data_.player_hands,
            this->data_.robot_hand
        );    
        
        // Run MonteCarlo Simulation
        this->data_.probability = MonteCarlo::run(
            this->settings_,
            Deck(this->data_.robot_hand),
            this->public_cards_,
            this->robot_cards_,
            this->log_sim_
        );         

        		// send cards to GUI if a GUI is connected
		if(this->gui_interface_ != nullptr)
		{
			this->gui_interface_->setData(this->data_);
		}

        this->robot_cards_.clear();
        this->public_cards_.clear();
    }

}// end namespace poker