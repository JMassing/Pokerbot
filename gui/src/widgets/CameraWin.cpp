#include "CameraWin.h"        

namespace gui
{

    bool CameraWin::content()
    {
         // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -8);  

        bool changed = false;
        // draw Gui Controls and check if any control was changed. If so, set this->cam_control_changes to true, else to false
        changed |= ImGui::Checkbox("Use Auto Focus", &this->config_.auto_focus); 
        changed |= ImGui::Checkbox("Use Auto Exposure", &this->config_.auto_exposure);
        changed |= ImGui::Checkbox("Use Auto White Balance", &this->config_.auto_wb); 
        changed |= ImGui::SliderInt("Exposure", &this->config_.exposure_time, this->config_.min_exp_time, this->config_.max_exp_time);
        ImGui::SameLine(); this->helpMarker("CTRL+click to input value. Value should be negative."); 
        this->enforceBoundaries( this->config_.min_exp_time, this->config_.max_exp_time, this->config_.exposure_time);

        changed |= ImGui::SliderInt("Focus", &this->config_.focus, this->config_.min_focus, this->config_.max_focus); 
        ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
        this->enforceBoundaries( this->config_.min_focus, this->config_.max_focus, this->config_.focus);

        changed |= ImGui::SliderInt("Brightness", &this->config_.brightness, this->config_.min_brightness, this->config_.max_brightness); 
        ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
        this->enforceBoundaries( this->config_.min_brightness, this->config_.max_brightness, this->config_.brightness);

        changed |= this->addButton("Reset", [this](){this->setConfigToDefault();});
        ImGui::SameLine(); 
        this->addButton("Save Settings", [this](){this->show_ask_for_save_ = true;}); 
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