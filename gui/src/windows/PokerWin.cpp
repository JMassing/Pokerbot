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

     
            // Show player hands
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
                    player_string = "Player" + std::to_string(player_nr) +  " Hand:";                                                                                  
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

            // Show Player Money
            ImGui::NewLine();
            player_nr = 0;
            for(const auto& player: this->poker_if_->data_.players)
            {
                std::string money_str = std::to_string(player.money);                
                std::string text = (player_nr < 1) ? "Robot money: " + money_str : 
                                                     "Player " + std::to_string(player_nr) 
                                                        + " money: " + money_str;

                ImGui::Text(text.c_str());
                ++player_nr;
            }                

            // Place Bets
            if(this->poker_if_->data_.game_phase == poker::PLACE_BETS)
            {
                this->show_place_bet_win_ = true;
                place_bet_win_.draw();
            }  
                                
            ImGui::End();
        }

    }
}