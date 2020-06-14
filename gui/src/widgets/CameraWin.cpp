#include "CameraWin.h"        

namespace gui
{

    bool CameraWin::content()
    {
         // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -8);  

        bool changed = false;

        changed |= ImGui::Checkbox("Use Auto Focus", &this->config_.auto_focus); 
        changed |= ImGui::Checkbox("Use Auto Exposure", &this->config_.auto_exposure);
        changed |= ImGui::Checkbox("Use Auto White Balance", &this->config_.auto_wb); 
        changed |= this->slider_.draw("Exposure", this->config_.min_exp_time, this->config_.max_exp_time, this->config_.exposure_time, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value. Value should be negative."); 
        changed |= this->slider_.draw("Focus", this->config_.min_focus, this->config_.max_focus, this->config_.focus, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
        changed |= this->slider_.draw("Brightness", this->config_.min_brightness, this->config_.max_brightness, this->config_.brightness, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");

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
        this->config_.device_id = this->default_config_->device_ID;
        this->config_.auto_exposure = this->default_config_->auto_exposure;
        this->config_.auto_focus = this->default_config_->auto_focus;
        this->config_.auto_wb = this->default_config_->auto_wb;
        this->config_.exposure_time = this->default_config_->exposure_time;
        this->config_.brightness = this->default_config_->brightness;
        this->config_.focus = this->default_config_->focus;
        this->config_.zoom = this->default_config_->zoom;
    }

	void CameraWin::saveConfigAsDefault()
    {
        this->default_config_->device_ID = this->config_.device_id;
        this->default_config_->auto_exposure = this->config_.auto_exposure;
        this->default_config_->auto_focus = this->config_.auto_focus;
        this->default_config_->auto_wb = this->config_.auto_wb;
        this->default_config_->exposure_time = this->config_.exposure_time;
        this->default_config_->brightness = this->config_.brightness;
        this->default_config_->focus = this->config_.focus;
        this->default_config_->zoom = this->config_.zoom;
        this->default_config_->saveConfig();
    };


} //end namespace gui