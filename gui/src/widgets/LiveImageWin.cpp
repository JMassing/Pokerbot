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
                this->drawer_.drawCards(
                    this->cards_, 
                    shown_image.image, 
                    this->controls_.card_outline_color
                    );
            }

  

            cv::Rect robot_area{};
            cv::Rect public_area{};

            robot_area.x = 160;
            robot_area.y = 260;
            robot_area.width = 320;
            robot_area.height = 200;

            public_area.x = 10;
            public_area.y = 100;
            public_area.width = 620;
            public_area.height = 150;   

            this->drawer_.drawRectangle(
                shown_image.image, 
                robot_area,
                cv::Scalar{0, 255, 0}
            ); 

            this->drawer_.drawRectangle(
                shown_image.image, 
                public_area,
                cv::Scalar{0, 0, 255}
            );                 

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