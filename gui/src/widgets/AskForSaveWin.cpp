#include "AskForSaveWin.h"        

namespace gui
{

    bool AskForSaveWin::content()
    {
        std::string text = "Save current " + this->type_ + " settings as default?\n" 
                            + "Config.ini will be overwritten.";
        ImGui::Text(text.c_str());
        this->addButton("Yes", [this](){this->save_ = true; this->show_ = false;}); ImGui::SameLine();
        this->addButton("No", [this](){this->save_ = false; this->show_ = false;});

        return save_;
    }

} //end namespace gui