#include "Game.hpp" 

namespace poker{
 
    void Game::play()
    { 
            // get settings from GUI if a GUI is connected
            if(this->gui_interface_ != nullptr)
            {
                if(this->gui_interface_->checkUserInput())
                {
                    this->sim_.updateSettings( this->gui_interface_->getSettings());
                }
            }

            // get detected cards from detection module if connected
            if(this->detect_interface_ != nullptr)
            {
                this->sim_.run(
                        detect_interface_->getData().robot_cards, 
                        detect_interface_->getData().public_cards,
                        this->data_
                    );
                
                // Set next game phase, if robot cards are saved
                if(detect_interface_->getData().robot_cards.size() == 2)
                {
                    this->data_.game_phase = 2;
                }
                this->detect_interface_->setGamePhase(this->data_.game_phase);
            }
            else
            {
                std::cout << "Can't run simulation! Detection Module Output is not connected." << std::endl;
            }

            
                    // send cards to GUI if a GUI is connected
            if(this->gui_interface_ != nullptr)
            {
                this->gui_interface_->setData(this->data_);
            }
    }

}// end namespace poker