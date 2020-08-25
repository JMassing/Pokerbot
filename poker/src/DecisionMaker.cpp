#include "DecisionMaker.hpp"

#include <iostream>

namespace poker{

    void DecisionMaker::decideBetsize()
    {
        int bet = 0;
        double winning_probability = this->data_.probability.first + this->data_.probability.second;
        if(this->data_.players.at(0).current_decision == CALL)
        {  
            bet = 
                this->data_.highest_bet <= this->data_.players.at(0).money ?
                (this->data_.highest_bet - this->data_.players.at(0).money_bet_in_phase) 
                : this->data_.players.at(0).money;
        }
        else if(this->data_.players.at(0).current_decision == RAISE)
        {
           
                if(winning_probability <= 80)
                {
                    bet = 
                        (static_cast<double>(this->data_.pot_size)/3.0 > 3 * this->big_blind_) ? 
                        static_cast<int>(static_cast<double>(this->data_.pot_size)/3.0) : 3 * this->big_blind_; 
                }
                else if(winning_probability > 80)
                {
                    bet = 
                        (2 * this->data_.highest_bet > 2 * this->data_.pot_size) ?
                        2 * this->data_.highest_bet : 2 * this->data_.pot_size;            
                }
                else
                {
                    //do nothing
                }

            // Check if robot went all in
            bet = bet <= this->data_.players.at(0).money ? bet : this->data_.players.at(0).money;            
            
            this->data_.players.at(0).current_decision = HAS_RAISED;
        }
        else
        {
            //do nothing
        }

        this->data_.players.at(0).current_bet = bet;
        this->data_.highest_bet =  bet + this->data_.players.at(0).money_bet_in_phase;

        
    }

    void DecisionMaker::decideMove()
    {
      
        double winning_probability = this->data_.probability.first + this->data_.probability.second;
        if(winning_probability <= 40)
        {
            if(this->data_.highest_bet > this->data_.players.at(0).money_bet_in_phase)
            {
                // Oponent has raised
                this->data_.players.at(0).current_decision = FOLD;
            }
            else
            {
                // Nobody has raised
                this->data_.players.at(0).current_decision = CHECK;
            }

        }
        else if(winning_probability > 40 && winning_probability <= 60)
        {
            if (this->data_.highest_bet > this->data_.players.at(0).money_bet_in_phase && 
                this->data_.highest_bet >= static_cast<double>(this->data_.pot_size)/3.0 && 
                this->data_.highest_bet >= 3*this->big_blind_ )
            {
                // Oponent has raised for too much money
                this->data_.players.at(0).current_decision = FOLD;
            }
            else if(this->data_.highest_bet == this->data_.players.at(0).money_bet_in_phase)
            {
                // Nobody has raised
                this->data_.players.at(0).current_decision = CHECK;
            }
            else
            {
                // Oponent has raised but not too much
                this->data_.players.at(0).current_decision = CALL;
            }
            
        }
        else if(winning_probability > 60 && winning_probability <= 80)
        {
            if (this->data_.highest_bet > this->data_.players.at(0).money_bet_in_phase && 
                this->data_.highest_bet >= 1/3 * this->data_.pot_size && 
                this->data_.highest_bet >= 3*this->big_blind_ )
            {
                // Only call if oponent raised for a high amount
                this->data_.players.at(0).current_decision = CALL;
            }
            else
            {
                // raise
                this->data_.players.at(0).current_decision = RAISE;
            }
        }
        else if(winning_probability > 80)
        {
            this->data_.players.at(0).current_decision = RAISE;
        }
        else
        {
            
        }           
    }

    void DecisionMaker::makeDecision()
    {
        this->decideMove();
        this->decideBetsize(); 
    }


}// end namespace poker