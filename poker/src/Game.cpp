#include "Game.hpp" 

namespace poker{

    bool Game::getWinner()
    {
        // Check if all players except for one have folded.
        int winner = -2;
        int nr_players_not_folded = 0;
        int i = 0;
        for(const auto& player: this->data_.players)
        {
            if(player.current_decision != FOLD )
            {
                winner = i;
                ++nr_players_not_folded;
            }
            ++i;
        }
        if(nr_players_not_folded <= 1)
        {
            this->data_.winner = winner;
            return true;
        }
        // After showdown winner is given by user input

        return false;
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
            this->controller_.start();
        }

        // stop game if stop was hit
        if(this->settings_.stop_game)
        {
            this->controller_.stop();
        }

        //stop game if players have less money than big blind left and we are at the beginning of the round
        if(this->money_tracker_.hasPlayerLessThanBigblind( this->settings_.big_blind) && this->game_phase_ == HAND_CARDS)
        {
            this->controller_.stop();
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
     
            this->controller_.setGamePhase();

            // get bets
            //skip player if folded or is all in
            if(this->data_.players.at(this->data_.whos_turn).has_folded)
            {
                this->data_.nextPlayer();
            }
            
            
            if( this->game_phase_ == BET_HAND || this->game_phase_ == BET_FLOP 
                || this->game_phase_ == BET_RIVER || this->game_phase_ == BET_TURN)
            {   
                // Check if its the players turn who made the highest bet. Then every other
                // player has called/folded and we set the decision to check to advance to the
                // next phase
                if( this->data_.players.at(this->data_.whos_turn).money_bet_in_phase == this->data_.highest_bet 
                    && this->data_.highest_bet != 0 
                    && this->data_.players.at(this->data_.whos_turn).current_decision != poker::NO_DECISION
                    && this->data_.players.at(this->data_.whos_turn).current_decision != poker::RAISE
                )
                {
                    this->data_.players.at(this->data_.whos_turn).current_decision = poker::CHECK;
                }      
                // go to next phase if a player went all in and all other players have called, else
                // process bet                         
                if (this->money_tracker_.isPlayerAllIn() && !this->decision_processor_.wasRaised())
                {
                    this->money_tracker_.processBet();
                    ++this->game_phase_;
                }
                else
                {
                    // Robot decides move of it is his turn and he hasn't decided and nobody raised 
                    // and nobody has won yet
                    if ( this->data_.whos_turn == 0 
                         && ( !this->decision_processor_.haveAllPlayersDecided() || this->decision_processor_.hasPlayerRaised() ) 
                         && !this->getWinner())
                    {
                        DecisionMaker decision_maker_(this->data_);
                        decision_maker_.makeDecision();
                        this->data_.nextPlayer();
                    }
                    else
                    {
                        //do nothing
                    }

                    this->money_tracker_.processBet();

                    // process player decisions if we do not have a winner
                    if(this->getWinner())
                    {
                        // next round window will show and next round will start when confirmed by user
                    }
                    else
                    {
                        if(this->decision_processor_.haveAllPlayersDecided())
                        {
                            if(!this->decision_processor_.wasRaised())
                            {
                                // all players have called or all folded and nobody is all in
                                this->controller_.resetPhase();
                                ++this->game_phase_;                  
                            }
                            else
                            {
                                    
                            }
                        }
                    }
                }
            }      

            this->getWinner();
  
            // get pot size
            this->money_tracker_.calcPotSize();

            // start next round, if user confirmed to start it
            if(this->data_.next_round && this->detect_interface_->getData().cards.size() == 0)
            {
                this->controller_.startNextRound();
            }
            else
            {
                this->data_.next_round = false;
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

        this->money_tracker_.isPlayerAllIn();
        // send hands and data to GUI if a GUI is connected
        if(this->gui_interface_ != nullptr)
        {
            this->data_.robot_cards = this->robot_cards_;
            this->data_.game_phase = this->game_phase_;
            this->gui_interface_->setData(this->data_);
        }

        // send game settings to settings window
        if(this->gui_interface_ != nullptr)
        {
            this->gui_interface_->setSettings(this->settings_);
        }
    }
}// end namespace poker