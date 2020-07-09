#include "PokerWind.hpp"

namespace gui{

    bool PokerWin::draw()
    {
         if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            ImGui::Text("Probability of winning = %.2f", 
                        static_cast<float>(this->data_.probability.first));

            ImGui::Text("Probability of winning tie = %.2f", 
                        static_cast<float>(this->data_.probability.second));

            ImGui::Text("Robot Hand:");
            ImGui::SameLine();
            for(const auto& card: this->data_.robot_hand.hand_)
            {   
                std::string text = this->mapping_.text_mappings.right.at(card.rank) + 
                this->mapping_.text_mappings.right.at(card.suit);
                ImGui::Text(text.c_str());
                ImGui::SameLine();
            }

            ImGui::NewLine();

            int player = 1;
            for(const auto& hand: this->data_.player_hands)
            {
                std::string player_string = "Player" + std::to_string(player) + 
                                            " Hand:";
                ImGui::Text(player_string.c_str());
                ImGui::SameLine();
                for(const auto& card: hand.hand_)
                {   
                    std::string text = 
                        this->mapping_.text_mappings.right.at(card.rank) + 
                        this->mapping_.text_mappings.right.at(card.suit);
                    ImGui::Text(text.c_str());
                    ImGui::SameLine();
                }
                ImGui::NewLine();
                ++player;
            }

            ImGui::End();
        }

        return true;
    }
}