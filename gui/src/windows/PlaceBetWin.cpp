#include "PlaceBetWin.hpp"   

namespace gui
{

    void PlaceBetWin::draw()
    {
        int whos_turn = this->poker_if_->data_.whos_turn;
        poker::Player& player_tmp = this->poker_if_->data_.players.at(whos_turn);

        if(this->poker_if_->data_.players.at(0).is_all_in && this->poker_if_->data_.highest_bet == player_tmp.money_bet_in_phase)
        {
            player_tmp.money += (player_tmp.money_bet_in_phase - this->poker_if_->data_.players.at(0).money_bet_in_phase);
            player_tmp.money_in_play -= (player_tmp.money_bet_in_phase - this->poker_if_->data_.players.at(0).money_bet_in_phase);
            player_tmp.money_bet_in_phase = this->poker_if_->data_.players.at(0).money_bet_in_phase;
            player_tmp.current_decision = poker::CALL;
            this->poker_if_->data_.nextPlayer();
            whos_turn++;
        }

        if(this->show_ && whos_turn > 0)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

       	    // Robot decision:
            std::string decision = "";
            switch (this->poker_if_->data_.players.at(0).current_decision)
            {
                case poker::NO_DECISION : decision = "not had his turn yet."; break;
                case poker::CHECK       : decision = "checked"; break;
                case poker::CALL        : decision = "called"; break;
                case poker::RAISE       : decision = "raised to " + std::to_string(this->poker_if_->data_.players.at(0).money_bet_in_phase); break;
                case poker::HAS_RAISED  : decision = "raised to " + std::to_string(this->poker_if_->data_.players.at(0).money_bet_in_phase); break;
            }

            std::string robot_decision = "Robot has " + decision;
            ImGui::Text(robot_decision.c_str());
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
                        this->poker_if_->data_.highest_bet - player_tmp.money_bet_in_phase <= player_tmp.money ?
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
            // can't raise if robot already went all in
            can_raise = this->poker_if_->data_.players.at(0).money <= 0 ? false : true;

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

            player_tmp.money -= player_tmp.current_bet;
            player_tmp.money_bet_in_phase += player_tmp.current_bet;

            ImGui::End();
        }
    }

} //end namespace gui