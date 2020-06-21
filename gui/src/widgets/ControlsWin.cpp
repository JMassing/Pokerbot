#include "ControlsWin.h"        

namespace gui
{

    bool ControlsWin::draw()
    {
        bool changed = false;

        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
            ImGui::PushItemWidth(ImGui::GetFontSize() * -15);  

            // Layout
            ImGui::Text("Live View Settings:");
            ImVec4 tmp_card_outline_color = ImVec4(static_cast<float>(this->card_outline_color_[2])/255.0f, 
                                                static_cast<float>(this->card_outline_color_[1])/255.0f, 
                                                static_cast<float>(this->card_outline_color_[0])/255.0f, 1.00f);
            changed |= ImGui::ColorEdit3("card outline color", (float*)&tmp_card_outline_color);
            this->card_outline_color_ = {tmp_card_outline_color.z*255.0f, tmp_card_outline_color.y*255.0f, tmp_card_outline_color.x*255.0f};
        
            if (ImGui::CollapsingHeader("Live View Size"))
            {
                changed |= this->button_.draw("800x600", true,  [this](){this->live_view_width_ = 800; this->live_view_height_ = 600;}); ImGui::SameLine();
                changed |= this->button_.draw("1024x768", true,  [this](){this->live_view_width_ = 1024; this->live_view_height_ = 768;}); ImGui::SameLine();
                changed |= this->button_.draw("1280x720", true,  [this](){this->live_view_width_ = 1280; this->live_view_height_ = 720;}); 
                changed |= this->button_.draw("1280x768", true,  [this](){this->live_view_width_ = 1280; this->live_view_height_ = 768;}); ImGui::SameLine();
                changed |= this->button_.draw("1280x800", true,  [this](){this->live_view_width_ = 1280; this->live_view_height_ = 800;}); ImGui::SameLine();
                changed |= this->button_.draw("1280x1024", true,  [this](){this->live_view_width_ = 1280; this->live_view_height_ = 1024;}); 
                changed |= this->button_.draw("1360x768", true,  [this](){this->live_view_width_ = 1360; this->live_view_height_ = 768;}); ImGui::SameLine();
                changed |= this->button_.draw("1366x768", true,  [this](){this->live_view_width_ = 1366; this->live_view_height_ = 768;}); ImGui::SameLine();
                changed |= this->button_.draw("1400x1050", true,  [this](){this->live_view_width_ = 1400; this->live_view_height_ = 1050;}); 
                changed |= this->button_.draw("1440x900", true,  [this](){this->live_view_width_ = 1440; this->live_view_height_ = 900;}); ImGui::SameLine();
                changed |= this->button_.draw("1600x900", true,  [this](){this->live_view_width_ = 1600; this->live_view_height_ = 900;}); ImGui::SameLine();
                changed |= this->button_.draw("1920x1080", true,  [this](){this->live_view_width_ = 1920; this->live_view_height_ = 1080;}); 
            }

            changed |= this->slider_.draw("Card Image Size", this->min_card_image_height_percent_, this->max_card_image_height_percent_, this->card_image_height_percent_, true); ImGui::SameLine(); this->helpMarker("Size of displayed card images in %. CTRL+click to input value.");
            changed |= this->slider_.draw("Rank/Suit Image Size", this->min_rank_suit_image_height_percent_, this->max_rank_suit_image_height_percent_, this->card_rank_suit_height_percent_, true); ImGui::SameLine(); this->helpMarker("Size of displayed rank and suit images in %. CTRL+click to input value.");

            // Camera Controls
            ImGui::NewLine();
            ImGui::Text("Camera Settings:");
            changed |= ImGui::Checkbox("Use Auto Focus", &this->camera_settings_.auto_focus); 
            changed |= ImGui::Checkbox("Use Auto Exposure", &this->camera_settings_.auto_exposure);
            changed |= ImGui::Checkbox("Use Auto White Balance", &this->camera_settings_.auto_wb); 
            changed |= this->slider_.draw("Exposure", this->min_exp_time_, this->max_exp_time_, this->camera_settings_.exposure_time, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value. Value should be negative."); 
            changed |= this->slider_.draw("Focus", this->min_focus_, this->max_focus_, this->camera_settings_.focus, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
            changed |= this->slider_.draw("Brightness", this->min_brightness_, this->max_brightness_, this->camera_settings_.brightness, true); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");

            // Image Processing
            ImGui::NewLine();
            ImGui::Text("Image Processing Settings:");
            changed |= this->slider_.draw("Card Threshold", this->min_live_th_, this->max_live_th_, this->live_threshold_, true);
            ImGui::SameLine(); this->helpMarker("Threshold for detecting cards in live image. CTRL+click to input value.");  

            changed |= this->slider_.draw("Rank/Suit Threshold",  this->min_bin_th_, this->max_bin_th_, this->identification_threshold_, true); 
            ImGui::SameLine(); this->helpMarker("Threshold for detecting rank and suit image in upper left corner of card. CTRL+click to input value.");  

            changed |= this->slider_.draw("Binarization Threshold", this->min_ident_th_, this->max_ident_th_, this->binary_threshold_, true); 
            ImGui::SameLine(); this->helpMarker("Threshold for binarizing detected rank and suit images. CTRL+click to input value.");  


            // Poker Simulation
            ImGui::NewLine();
            ImGui::Text("Poker Simulation Settings:");
            changed |= this->input_.draw("# of Opponents", this->min_players_, this->max_players_, this->nr_of_human_players_, true); ImGui::SameLine(); this->helpMarker("Nr of opponents playing against the bot.");  
            changed |= this->slider_.draw("# of simulation runs", this->min_sim_runs_, this->max_sim_runs_, this->nr_of_simulation_runs_, true);

            changed |= this->button_.draw("Reset", true, [this](){this->setConfigToDefault();}); 
            ImGui::SameLine();
            this->button_.draw("Save Settings", true, [this](){this->show_ask_for_save_ = true;}); 

        }
        ImGui::End();

        if(changed)
        {
            this->notify();
        }

        return changed;
    }

    void ControlsWin::setConfigToDefault()
    {}

	void ControlsWin::saveConfigAsDefault()
    {};


} //end namespace gui