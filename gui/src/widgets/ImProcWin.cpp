#include "ImProcWin.h"        

namespace gui
{

    bool ImProcWin::content()
    {
        bool changed = false;
        // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -15);  
        
        changed |= this->slider_.draw("Card Threshold", this->config_.min_live_th, this->config_.max_live_th, this->config_.live_threshold, true);
        ImGui::SameLine(); this->helpMarker("Threshold for detecting cards in live image. CTRL+click to input value.");  

        changed |= this->slider_.draw("Rank/Suit Threshold",  this->config_.min_bin_th, this->config_.max_bin_th, this->config_.identification_threshold, true); 
        ImGui::SameLine(); this->helpMarker("Threshold for detecting rank and suit image in upper left corner of card. CTRL+click to input value.");  

        changed |= this->slider_.draw("Binarization Threshold", this->config_.min_ident_th, this->config_.max_ident_th, this->config_.binary_threshold, true); 
        ImGui::SameLine(); this->helpMarker("Threshold for binarizing detected rank and suit images. CTRL+click to input value.");  

        changed |= this->button_.draw("Reset", true, [this](){this->setConfigToDefault();}); 
        ImGui::SameLine();
        this->button_.draw("Save Settings", true, [this](){this->show_ask_for_save_ = true;}); 
      
        if(this->show_ask_for_save_ == true)
        {
            if(this->save_win_.draw(this->show_ask_for_save_))
            {
                this->saveConfigAsDefault();
            }
        }
        
        return changed;
    }

    void ImProcWin::setConfigToDefault()
    {   
        config_.live_threshold = this->default_config_->live_threshold;
        config_.binary_threshold = this->default_config_->binary_threshold;
        config_.identification_threshold = this->default_config_->identification_threshold;
    }

	void ImProcWin::saveConfigAsDefault()
    {
        this->default_config_->live_threshold = config_.live_threshold;
        this->default_config_->binary_threshold = config_.binary_threshold;
        this->default_config_->identification_threshold = config_.identification_threshold;
        this->default_config_->saveConfig();
    };


} //end namespace gui