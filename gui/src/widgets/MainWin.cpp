#include "MainWin.h"        

namespace gui
{

    bool MainWin::content()
    {
        bool should_close = false;
                // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);  
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        this->button_.draw("Quit Program", true, [&should_close](){should_close = true;});
        return should_close;
    }

} //end namespace gui