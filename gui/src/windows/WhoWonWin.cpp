#include "WhoWonWin.hpp"        

namespace gui
{

    void WhoWonWin::draw()
    {
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            ImGui::Text("Enter Player who won the showdown.\nFor a tie enter -1. If Robot won enter a 0");

                this->input_field_.draw("Winner", -1, this->poker_if_->data_.players.size()-1, this->winner_, true);
                this->button_.draw("Confirm", true, 
                    [this](){
                        this->poker_if_->data_.winner = this->winner_;
                        this->winner_ = -1;
                        this->show_ = false;
                     }
                    ); 

            ImGui::End();
        }
    }

} //end namespace gui