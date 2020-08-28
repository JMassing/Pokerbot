#include "CardImageWin.hpp"        

namespace gui
{

    void CardImageWin::draw()
    {        
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            int height = static_cast<int>( 
                this->image_height_ * 
                static_cast<double>(this->controls_.card_image_height_percent)/100.0
                );

            int width = static_cast<int>(static_cast<double>(height)/this->aspect_ratio_);

            cv::Mat shown_img;
            std::vector<cv::Mat> image_vector;

            for(const auto& card : this->cards_)
            {
                if(this->poker_if_->isCardMasked(this->controls_.mask_robot_cards, card))
                {
                    //don't show masked cards
                }
                else
                {
                    if(image_vector.size() == 0)
                    { 
                        image_vector.emplace_back(card.card_image.image); 
                    }
                    else if(image_vector.size() > 0 && card.card_image.image.cols == image_vector.at(0).cols)
                    {
                        image_vector.emplace_back(card.card_image.image); 
                    }
                    else
                    {
                        //Do nothing
                    }                     
                }
            }   

            if(image_vector.size()>0)
            {
                cv::hconcat(image_vector, shown_img);

                this->drawer_.draw(
                    shown_img, 
                    width*image_vector.size(), 
                    height
                    );   
            }

            ImGui::End();
        }
        
    }

} //end namespace gui