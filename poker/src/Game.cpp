#include "Game.hpp" 

namespace poker{
 
    void Game::start()
    {
        // Initialize players and set money equal to starting money
         this->data_.players.resize(
            this->settings_.nr_of_human_players + 1, Player(this->starting_money_)
            );

        // Roll die on who starts the first turn of the game. 
        // Use player + 1 as die always starts at 1 and Robot = 0
        std::random_device rd;
        std::mt19937 g(rd());


        // Determine who has the button first it is
        this->data_.button_pos = 
            templates::rollDie(this->settings_.nr_of_human_players + 1, g) - 1;
        
        // The third player after the button makes the first bet because of blinds
        this->data_.whos_turn = 
            (this->data_.button_pos + 3) % (this->settings_.nr_of_human_players + 1);
        
        this->game_phase_ = HAND_CARDS;
    }

    void Game::stop()
    {
        this->data_.players.clear();
        this->robot_cards_.clear();
        this->public_cards_.clear();
        this->data_.robot_hand.reset();
        this->data_.player_hands.clear();
        this->data_.probability = {0,0};
        this->game_phase_ = NOT_STARTED;
    }

    void Game::processBet(int bet_size)
    {
        this->data_.players.at(this->data_.whos_turn).money -= bet_size; 
    }

    void Game::play()
    { 
        // get settings from GUI if a GUI is connected
        if(this->gui_interface_ != nullptr)
        {
            if(this->gui_interface_->checkUserInput())
            {
                this->settings_ = this->gui_interface_->getSettings();
            }
        }

        // Get Player Decisions from GUI
        if(this->gui_interface_ != nullptr)
        {
            this->data_ = this->gui_interface_->getData();            
        }

        // start game
        if(this->settings_.start_game)
        {
            this->start();
            this->settings_.start_game = false;
        }

        // stop game
        if(this->settings_.stop_game)
        {
            this->stop();
            this->settings_.stop_game = false;
        }

        // Play actual game. Detection interface has to be connected, to get cards.
        // Game has to be started
        if(this->detect_interface_ != nullptr && this->game_phase_ > NOT_STARTED)
        {

            // Assign Cards to Robot or Public Cards  
            CardAssigner::assignCards(
                this->detect_interface_->getData().cards, 
                this->public_cards_, 
                this->robot_cards_, 
                this->game_phase_
                );

            // Build hands for players
            HandBuilder::buildHands(
                this->public_cards_,
                this->robot_cards_,
                this->data_.players
                );                

            // Run simulation
           this->data_.probability = 
                MonteCarlo::run(
                    this->settings_.nr_of_simulation_runs, 
                    Deck(this->data_.players.at(0).hand),
                    this->data_.players,
                    this->game_phase_
                    );

            // Set next game phase, if robot cards are saved
            if(robot_cards_.size() == 2)
            {
                this->game_phase_ = PLACE_BETS;
            }          

            // get bets
            if( this->game_phase_ == PLACE_BETS)
            {
                this->processBet(this->gui_interface_->getBetSize());
            }      
        }
        else if(this->detect_interface_ == nullptr && this->game_phase_ > NOT_STARTED)
        {
            std::cout << "Can't run simulation! Detection Module Output is not connected." << std::endl;
        }
        else
        {
            // do nothing
        }
           
        // send hands to GUI if a GUI is connected
        if(this->gui_interface_ != nullptr)
        {
            this->data_.game_phase = this->game_phase_;
            this->gui_interface_->setData(this->data_);
        }
    }

}// end namespace poker