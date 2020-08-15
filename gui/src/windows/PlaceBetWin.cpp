#include "PlaceBetWin.hpp"        

namespace gui
{

    void PlaceBetWin::draw()
    {
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            int whos_turn = this->poker_if_->data_.whos_turn;
            poker::Player& player_tmp = this->poker_if_->data_.players.at(whos_turn);

            // Check if its the players turn who made the highest bet. Then every other
            // player has called/folded and we set the decision to call to advance to the
            // next phase
            if( player_tmp.money_bet_in_phase == this->poker_if_->data_.highest_bet && 
                this->poker_if_->data_.highest_bet != 0 && player_tmp.current_decision != poker::NO_DECISION
                && player_tmp.current_decision != poker::RAISE)
            {
                player_tmp.current_decision = poker::CHECK;
            }    

            std::string text = "Player " + std::to_string(whos_turn) + " your turn.";          
            ImGui::Text(text.c_str());

            // You can only check, if you have bet as much as the highest bet
            bool can_check = (player_tmp.money_bet_in_phase == this->poker_if_->data_.highest_bet) 
                ? true : false;
            this->button_.draw("Check", can_check, 
                [this, &player_tmp](){
                    player_tmp.current_decision = poker::CHECK;
                    this->poker_if_->data_.nextPlayer();
                    }
                );
            ImGui::SameLine();

            this->button_.draw("Call", true, 
                [this, &player_tmp](){
                    player_tmp.current_decision = poker::CALL;
                    player_tmp.current_bet = 
                        this->poker_if_->data_.highest_bet <= player_tmp.money ?
                        (this->poker_if_->data_.highest_bet - player_tmp.money_bet_in_phase) 
                        : player_tmp.money;
                    this->poker_if_->data_.nextPlayer();
                    }
                );
            ImGui::SameLine();

            this->button_.draw("Fold", true, 
                [this, &player_tmp](){
                    player_tmp.current_decision = poker::FOLD;
                    player_tmp.has_folded = true;
                    this->poker_if_->data_.nextPlayer();
                    }
                );
            ImGui::SameLine();

            bool can_raise = this->poker_if_->data_.highest_bet <= player_tmp.money ? true : false;
            this->button_.draw("Raise", can_raise, 
                [this, &player_tmp](){player_tmp.current_decision = poker::RAISE;});   
           
            if(player_tmp.current_decision == poker::RAISE)
            {
                this->input_field_.draw(
                    "Bet size", 
                    this->poker_if_->data_.highest_bet - player_tmp.money_bet_in_phase, 
                    player_tmp.money, 
                    this->bet_size_, true
                    );
                this->button_.draw("Place Bet", true, 
                    [this, &player_tmp](){
                        player_tmp.current_bet = this->bet_size_;
                        this->poker_if_->data_.highest_bet = this->bet_size_ + player_tmp.money_bet_in_phase;
                        this->bet_size_ = 0;
                        player_tmp.current_decision = poker::HAS_RAISED;
                        this->poker_if_->data_.nextPlayer(); 
                        }
                    );  
            }

            ImGui::End();
        }
    }

} //end namespace gui