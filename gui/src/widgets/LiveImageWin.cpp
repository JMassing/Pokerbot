#include "LiveImageWin.hpp"        

namespace gui
{

    bool LiveImageWin::draw()
    {      
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            
            capture::Image shown_image = this->live_frame_;

            if(this->controls_.show_cards && this->cards_.size() > 0)
            {
                this->visualize_.drawCards(
                    this->cards_, 
                    shown_image.image, 
                    this->controls_.card_outline_color
                    );
            }

            this->drawer_.draw(
                shown_image.image, 
                this->controls_.live_view_width, 
                this->controls_.live_view_height
                );
                
            ImGui::End();
        }

        return true;
    }
    
} //end namespace gui