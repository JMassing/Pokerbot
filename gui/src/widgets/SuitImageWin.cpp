#include "SuitImageWin.hpp"        

namespace gui
{

    bool SuitImageWin::draw()
    {        
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            int height = static_cast<int>( 
                this->image_height_ * 
                static_cast<double>(this->controls_.card_rank_suit_height_percent)/100.0
                );

            int width = static_cast<int>(static_cast<double>(height)/this->aspect_ratio_);

            for(const auto& card : this->cards_)
            {
                this->drawer_.draw(
                    card.suit_image.image, 
                    width, 
                    height
                    ); 
                ImGui::SameLine();
            }    

            ImGui::End();
        }

        return true;
        
    }

} //end namespace gui