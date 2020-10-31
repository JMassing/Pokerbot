#include "NextRoundWin.hpp"        

namespace gui
{

    void NextRoundWin::draw()
    {
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);
            
            std::string winner_text = "";
            if(this->poker_if_->data_.winner == -1)
            {
                winner_text = "We have a tie.";
            }
            else
            {
                std::string winner_string = (this->poker_if_->data_.winner == 0) ?
                    "Robot" : ("Player " + std::to_string(this->poker_if_->data_.winner));
                winner_text = winner_string + " has won!";
            }
            ImGui::Text(winner_text.c_str());
            ImGui::Text("Please remove all cards and hit next to start next round.");

            this->button_.draw("Next", true, 
                    [this](){ 
                        this->poker_if_->data_.next_round = true;
                        this->show_ = false;}
                    );  
            ImGui::End();
        }
    }

} //end namespace gui