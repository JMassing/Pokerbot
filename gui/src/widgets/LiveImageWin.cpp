#include "LiveImageWin.h"        

namespace gui
{

    bool LiveImageWin::draw()
    {      
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            this->drawer_.draw(
                this->live_frame_.image, 
                this->controls_.live_view_width_, 
                this->controls_.live_view_height_
                );
                
            ImGui::End();
        }

        return true;
    }
    
} //end namespace gui