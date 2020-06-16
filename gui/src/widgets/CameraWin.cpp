#include "CameraWin.h"        

namespace gui
{

    bool CameraWin::content()
    {
         // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -8);  

        bool changed = false;

        changed |= ImGui::Checkbox("Use Auto Focus", &this->camera_controls_->auto_focus); 
        changed |= ImGui::Checkbox("Use Auto Exposure", &this->camera_controls_->auto_exposure);
        changed |= ImGui::Checkbox("Use Auto White Balance", &this->camera_controls_->auto_wb); 
        changed |= this->slider_.draw("Exposure", this->min_exp_time_, this->max_exp_time_, this->camera_controls_->exposure_time, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value. Value should be negative."); 
        changed |= this->slider_.draw("Focus", this->min_focus_, this->max_focus_, this->camera_controls_->focus, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
        changed |= this->slider_.draw("Brightness", this->min_brightness_, this->max_brightness_, this->camera_controls_->brightness, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");

        changed |= this->button_.draw("Reset", true, [this](){this->setConfigToDefault();});
        ImGui::SameLine(); 
        changed |= this->button_.draw("Save Settings", true, [this](){this->show_ask_for_save_ = true;});
        
        if(this->show_ask_for_save_ == true)
        {
            if(this->save_win_.draw(this->show_ask_for_save_))
            {
                this->saveConfigAsDefault();
            }
        }
        
        return changed;
    }

    void CameraWin::setConfigToDefault()
    {   
        this->camera_controls_->device_ID = this->default_config_->device_ID;
        this->camera_controls_->auto_exposure = this->default_config_->auto_exposure;
        this->camera_controls_->auto_focus = this->default_config_->auto_focus;
        this->camera_controls_->auto_wb = this->default_config_->auto_wb;
        this->camera_controls_->exposure_time = this->default_config_->exposure_time;
        this->camera_controls_->brightness = this->default_config_->brightness;
        this->camera_controls_->focus = this->default_config_->focus;
        this->camera_controls_->zoom = this->default_config_->zoom;
    }

	void CameraWin::saveConfigAsDefault()
    {
        this->default_config_->device_ID = this->camera_controls_->device_ID;
        this->default_config_->auto_exposure = this->camera_controls_->auto_exposure;
        this->default_config_->auto_focus = this->camera_controls_->auto_focus;
        this->default_config_->auto_wb = this->camera_controls_->auto_wb;
        this->default_config_->exposure_time = this->camera_controls_->exposure_time;
        this->default_config_->brightness = this->camera_controls_->brightness;
        this->default_config_->focus = this->camera_controls_->focus;
        this->default_config_->zoom = this->camera_controls_->zoom;
        this->default_config_->saveConfig();
    };


} //end namespace gui