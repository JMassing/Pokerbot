#include "AskForSaveWin.hpp"        

namespace gui
{

    void AskForSaveWin::draw()
    {
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            std::string text = "Save current settings as default?\n Config.ini will be overwritten.";          
            ImGui::Text(text.c_str());

            this->button_.draw("Yes", true, 
                [this](){this->save_ = true; this->show_ = false;}); ImGui::SameLine();
                
            this->button_.draw("No", true, 
                [this](){this->save_ = false; this->show_ = false;}); ImGui::SameLine();
            
            ImGui::End();
        }
    }

} //end namespace gui