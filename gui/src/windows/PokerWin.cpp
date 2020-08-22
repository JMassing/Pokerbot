#include "PokerWin.hpp"

namespace gui{

    void PokerWin::draw()
    {
         if(this->show_)
        {
            // Show probability of winning
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            if(this->layout_settings_.show_probability)
            {
                ImGui::Text("Probability of winning = %.2f", 
                            static_cast<float>(this->poker_if_->data_.probability.first));
            
                ImGui::Text("Probability of winning tie = %.2f", 
                            static_cast<float>(this->poker_if_->data_.probability.second));
            }

     
            int player_nr = 0;
            for(const auto& player: this->poker_if_->data_.players)
            {
                std::string player_string = "";
                if(this->layout_settings_.show_robot_hand && player_nr == 0)
                {
                    // Show Robot hand
                    player_string = "Robot Hand";
                }
                else if(!this->layout_settings_.show_robot_hand && player_nr == 0)
                {
                    // Don't show Robot hand and go to next player
                   continue;
                }
                else
                {
                    player_string = "Player " + std::to_string(player_nr) +  " Hand:";                                                                                  
                }

                ImGui::Text(player_string.c_str());
                ImGui::SameLine();

                for(const auto& card: player.hand.cards_)
                {   
                    std::string text = 
                        this->mapping_.text_mappings.right.at(card.rank) + 
                        this->mapping_.text_mappings.right.at(card.suit);

                    ImGui::Text(text.c_str());
                    ImGui::SameLine();
                }
                ImGui::NewLine();
                ++player_nr;
            }

         
              // Game Information
            int phase = this->poker_if_->data_.game_phase;

            // show who has the button
            if(phase != poker::NOT_STARTED)
            {
                ImGui::NewLine();
                std::string button_string = (this->poker_if_->data_.button_pos == 0) ? 
                    "Robot" : ("Player " + std::to_string(this->poker_if_->data_.button_pos));  
                std::string button_text = button_string + " has button";
                ImGui::Text(button_text.c_str());
            
                // Show Player Money and currend bet
                player_nr = 0;
                for(const auto& player: this->poker_if_->data_.players)
                {
                    std::string money_str = std::to_string(player.money);    
                    std::string bet_str = (player.current_decision == poker::FOLD) ?
                        "FOLD" : std::to_string(player.money_bet_in_phase);                
                
                    std::string text = (player_nr < 1) ? 
                        "Robot money: " + money_str + ", Bet size: " + bet_str :    
                        "Player " + std::to_string(player_nr) + " money: " + money_str + 
                        ", Bet size: " + bet_str;

                    ImGui::Text(text.c_str());
                    ++player_nr;
                }        

                  // show pot size
                std::string pot_size = "Pot size: " + std::to_string(this->poker_if_->data_.pot_size);       
                ImGui::Text(pot_size.c_str()); 
            }

            // Place Bets
            if( (phase == poker::BET_HAND || phase == poker::BET_FLOP ||
                phase == poker::BET_RIVER || phase == poker::BET_TURN) 
                && this->poker_if_->data_.winner < -1 )
            {
                this->show_place_bet_win_ = true;
                place_bet_win_.draw();
            }  

            //Check who won in showdown
            if(phase == poker::SHOW_DOWN && this->poker_if_->data_.winner < -1)
            {
                this->show_who_won_win_ = true;
                who_won_win_.draw();
            }

            // Next round if we have a winner
            if(this->poker_if_->data_.winner >= -1)
            {
                this->show_next_round_win_ = true;
                this->next_round_win_.draw();
            }
                                
            ImGui::End();
        }

    }
}