#include "LiveImageWin.hpp"        

namespace gui
{
    void LiveImageWin::print_instructions(cv::Mat& live_image)
    {
        std::string instructions = "";
        switch(this->game_state_)
        {
            case 1: instructions = "Deal Robot Hand Cards."; break;
            case 2: instructions = "Deal flop."; break;
            case 3: instructions = "Deal turn."; break;
            case 4: instructions = "Deal river."; break;
            default: instructions = "";
        }

        int pos_x = static_cast<int>(this->controls_.live_view_width/2.0 - instructions.size()/2.0);
        int pos_y = this->controls_.live_view_height - 50;
        cv::Scalar color{0, 255, 0};
        cv::Point pos{20, 20};

        this->drawer_.printText(live_image, instructions, pos, color);
    }

    void LiveImageWin::draw()
    {      
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            
            Image shown_image = this->live_frame_;

            if(this->controls_.show_cards && this->cards_.size() > 0)
            {
                this->drawer_.drawCards(
                    this->cards_, 
                    shown_image.image, 
                    this->controls_.card_outline_color,
                    this->controls_.mask_robot_cards
                    );
            }              

            if(this->game_state_ != 0)
            {
                this->print_instructions(shown_image.image);
            }

            this->drawer_.draw(
                shown_image.image, 
                this->controls_.live_view_width, 
                this->controls_.live_view_height
                );
                
            ImGui::End();
        }

    }
    
} //end namespace gui