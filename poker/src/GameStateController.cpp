#include "GameStateController.hpp" 

namespace poker{

 
    void GameStateController::start()
    {
        // Initialize players and set money equal to starting money
         this->data_.players.resize(
            this->settings_.nr_of_human_players + 1, Player( this->settings_.starting_money)
            );

        // Roll die on who starts the first turn of the game. 
        // Use player + 1 as die always starts at 1 and Robot = 0
        std::random_device rd;
        std::mt19937 g(rd());

        // Determine who has the button first. -1 because rollDie starts at 1
        this->data_.button_pos = 
            templates::rollDie(this->settings_.nr_of_human_players + 1, g) - 1;
        
        this->startNextRound();
        this->settings_.start_game = false;
        this->settings_.playing_game = true;
    }

    void GameStateController::stop()
    {
        this->data_.players.clear();
        this->robot_cards_.clear();
        this->public_cards_.clear();
        this->data_.probability = {0,0};
        this->game_phase_ = NOT_STARTED;
        this->data_.highest_bet = 0;
        this->settings_.stop_game = false;
        this->settings_.playing_game = false;
    }

    void GameStateController::resetPhase()
    {
        for(auto& player: this->data_.players)
        {
            player.current_decision = NO_DECISION;
            player.current_bet = 0;
            player.money_bet_in_phase = 0;
        }
        this->data_.highest_bet = 0;
        this->data_.whos_turn =
            (this->data_.button_pos + 1) % (this->settings_.nr_of_human_players + 1);
    }

    void GameStateController::startNextRound()
    {
        this->resetPhase();
        this->game_phase_ = HAND_CARDS;
        this->data_.button_pos = 
            (this->data_.button_pos + 1) % (this->settings_.nr_of_human_players + 1);
        this->data_.whos_turn = 
            (this->data_.button_pos + 3) % (this->settings_.nr_of_human_players + 1);

        //add pot to winner or tie pot
        if(this->data_.winner >= 0)
        {
            this->data_.players.at(this->data_.winner).money += this->data_.pot_size;
        }
        else
        {
            // we had a tie, everybody gets their money back
            for(auto& player: this->data_.players)
            {
                player.money += player.money_in_play;
            }
        }
        
        for(auto& player: this->data_.players)
        {
            player.hand.reset();
            player.money_in_play = 0;
            player.has_folded = false;
            player.is_all_in = false;
        }        

        // reset winner
        this->data_.winner = -2;
        this->data_.next_round = false;

        //clear robot cards
        this->robot_cards_.clear();

        //set blinds
        int big_blind_pos= 
            (this->data_.button_pos + 2) % (this->settings_.nr_of_human_players + 1);
        int small_blind_pos = 
            (this->data_.button_pos + 1) % (this->settings_.nr_of_human_players + 1);        
        this->data_.highest_bet =  this->settings_.big_blind;
        this->data_.players.at(big_blind_pos).money_bet_in_phase = this->settings_.big_blind;
        this->data_.players.at(big_blind_pos).money_in_play =  this->settings_.big_blind;
        this->data_.players.at(big_blind_pos).money -=  this->settings_.big_blind;
        this->data_.players.at(small_blind_pos).money_bet_in_phase =  this->settings_.small_blind;
        this->data_.players.at(small_blind_pos).money_in_play =  this->settings_.small_blind;
        this->data_.players.at(small_blind_pos).money -= this->settings_.small_blind;
    }

   
    void GameStateController::setGamePhase()
    {
        // Set next game phase, if robot cards are saved
        if(this->game_phase_ == HAND_CARDS && this->robot_cards_.size() == 2)
        {
            this->game_phase_ = BET_HAND;
        }       
        // Set next game phase, if flop cards are saved
        else if(this->game_phase_ == FLOP && this->public_cards_.size() == 3)
        {
            this->game_phase_ = BET_FLOP;
        }     
        // Set next game phase, if turn card is saved
        else if(this->game_phase_ == TURN && this->public_cards_.size() == 4)
        {
            this->game_phase_ = BET_TURN;
        }     
        // Set next game phase, if river card is saved
        else if(this->game_phase_ == RIVER && this->public_cards_.size() == 5)
        {
            this->game_phase_ = BET_RIVER;
        }     
        else
        {
            // do nothing
        }

    }

}// end namespace poker