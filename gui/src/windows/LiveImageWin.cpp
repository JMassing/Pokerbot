#include "LiveImageWin.hpp"        

namespace gui
{
    void LiveImageWin::print_instructions(cv::Mat& live_image)
    {
        std::string instructions = "";
        switch(this->data_poker_.game_phase)
        {
            case 1: instructions = "Deal Robot Hand Cards."; break;
            case 2: instructions = "Place Bets."; break;
            case 3: instructions = "Deal flop."; break;
            case 4: instructions = "Place Bets."; break;
            case 5: instructions = "Deal turn."; break;
            case 6: instructions = "Place Bets."; break;
            case 7: instructions = "Deal river."; break;
            case 8: instructions = "Place Bets."; break;
            case 9: instructions = "Showdown."; break;
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
               
                for(const auto& card: this->cards_)
                {
                    // mask card if we want to mask robot cards and are befor flop since there 
                    // should only be robot cards in the image
                    bool mask_card = ( this->controls_.mask_robot_cards && 
                                        this->data_poker_.game_phase < poker::FLOP) ? 
                                        true : false;
                    // also mask robot cards in later stages if they are still there. 
                    // For show down they should be unmasked. 
                    if( this->controls_.mask_robot_cards && 
                        this->data_poker_.game_phase >= poker::FLOP && 
                        this->data_poker_.game_phase < poker::SHOW_DOWN &&
                        templates::contains(this->data_poker_.robot_cards.begin(), 
                                            this->data_poker_.robot_cards.end(), card) 
                      )
                    {
                        mask_card = true;
                    }
                    else
                    {
                        //do nothing
                    }

                    this->drawer_.drawCard(
                        card, 
                        shown_image.image, 
                        this->controls_.card_outline_color,
                        mask_card
                        );
                }
            }              

            if(this->data_poker_.game_phase != 0)
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