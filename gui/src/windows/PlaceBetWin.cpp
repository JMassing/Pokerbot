#include "PlaceBetWin.hpp"        

namespace gui
{

    void PlaceBetWin::draw()
    {
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            int whos_turn = this->poker_if_->data_.whos_turn;
            int bet_size = 0;

            std::string text = "Player " + std::to_string(whos_turn) + " your turn.";          
            ImGui::Text(text.c_str());

            this->button_.draw("Call", true, 
                [this, whos_turn](){this->poker_if_->data_.players.at(whos_turn).current_decision = poker::CALL;});
            ImGui::SameLine();
            this->button_.draw("Fold", true, 
                [this, whos_turn](){this->poker_if_->data_.players.at(whos_turn).current_decision = poker::FOLD;});
            ImGui::SameLine();
            this->button_.draw("Raise", true, 
                [this, whos_turn](){this->poker_if_->data_.players.at(whos_turn).current_decision = poker::RAISE;});   
           
            if(this->poker_if_->data_.players.at(whos_turn).current_decision == poker::RAISE)
            {
                this->input_field_.draw("Bet size", 0,  this->poker_if_->data_.players.at(whos_turn).money, bet_size, true);
                this->button_.draw("Place Bet", true, 
                    [this, whos_turn, bet_size](){
                        this->poker_if_->data_.players.at(whos_turn).current_bet = bet_size; 
                        }
                    );  
            }
            
            ImGui::End();
        }
    }

} //end namespace gui