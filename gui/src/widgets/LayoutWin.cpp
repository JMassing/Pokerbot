#include "LayoutWin.h"        

namespace gui
{

    bool LayoutWin::content()
    {
        bool changed = false;
        // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -14);  

        changed |= ImGui::Checkbox("Show Card Outline", &this->config_->show_cards);ImGui::SameLine(); this->helpMarker("If checked, outline of cards and cards rank/suit are displayed in the live image.");  
        ImVec4 tmp_card_outline_color = ImVec4(static_cast<float>(this->config_->card_outline_color[2])/255.0f, 
                                               static_cast<float>(this->config_->card_outline_color[1])/255.0f, 
                                               static_cast<float>(this->config_->card_outline_color[0])/255.0f, 1.00f);
        changed |= ImGui::ColorEdit3("card outline color", (float*)&tmp_card_outline_color);
        this->config_->card_outline_color = {tmp_card_outline_color.z*255.0f, tmp_card_outline_color.y*255.0f, tmp_card_outline_color.x*255.0f};
        changed |= ImGui::Checkbox("Show Camera Controls", &this->config_->show_camera_control);
        changed |= ImGui::Checkbox("Show Image Processing Settings", &this->config_->show_im_proc_settings_window);
        changed |= ImGui::Checkbox("Show Card Images", &this->config_->show_card_images); ImGui::SameLine(); this->helpMarker("If checked, card images extracted from live frame are displayed.");
        changed |= ImGui::Checkbox("Show Rank Images", &this->config_->show_rank_images); ImGui::SameLine(); this->helpMarker("If checked, binarized rank images extracted from card images are displayed.");
        changed |= ImGui::Checkbox("Show Suit Images", &this->config_->show_suit_images); ImGui::SameLine(); this->helpMarker("If checked, binarized suit images extracted from card images are displayed.");

        if (ImGui::CollapsingHeader("Live Image Size"))
        {
            changed |= this->button_.draw("800x600", true,  [this](){this->config_->live_image_width = 800; this->config_->live_image_height = 600;}); ImGui::SameLine();
            changed |= this->button_.draw("1024x768", true,  [this](){this->config_->live_image_width = 1024; this->config_->live_image_height = 768;}); ImGui::SameLine();
            changed |= this->button_.draw("1280x720", true,  [this](){this->config_->live_image_width = 1280; this->config_->live_image_height = 720;}); 
            changed |= this->button_.draw("1280x768", true,  [this](){this->config_->live_image_width = 1280; this->config_->live_image_height = 768;}); ImGui::SameLine();
            changed |= this->button_.draw("1280x800", true,  [this](){this->config_->live_image_width = 1280; this->config_->live_image_height = 800;}); ImGui::SameLine();
            changed |= this->button_.draw("1280x1024", true,  [this](){this->config_->live_image_width = 1280; this->config_->live_image_height = 1024;}); 
            changed |= this->button_.draw("1360x768", true,  [this](){this->config_->live_image_width = 1360; this->config_->live_image_height = 768;}); ImGui::SameLine();
            changed |= this->button_.draw("1366x768", true,  [this](){this->config_->live_image_width = 1366; this->config_->live_image_height = 768;}); ImGui::SameLine();
            changed |= this->button_.draw("1400x1050", true,  [this](){this->config_->live_image_width = 1400; this->config_->live_image_height = 1050;}); 
            changed |= this->button_.draw("1440x900", true,  [this](){this->config_->live_image_width = 1440; this->config_->live_image_height = 900;}); ImGui::SameLine();
            changed |= this->button_.draw("1600x900", true,  [this](){this->config_->live_image_width = 1600; this->config_->live_image_height = 900;}); ImGui::SameLine();
            changed |= this->button_.draw("1920x1080", true,  [this](){this->config_->live_image_width = 1920; this->config_->live_image_height = 1080;}); 
        }

        changed |= this->slider_.draw("Card Image Size", this->min_card_image_height_percent_, this->max_card_image_height_percent_, this->config_->card_image_height_percent, true); ImGui::SameLine(); this->helpMarker("Size of displayed card images in %. CTRL+click to input value.");
        changed |= this->slider_.draw("Rank/Suit Image Size", this->min_rank_suit_image_height_percent_, this->max_rank_suit_image_height_percent_, this->config_->card_rank_suit_height_percent, true); ImGui::SameLine(); this->helpMarker("Size of displayed rank and suit images in %. CTRL+click to input value.");

        changed |= this->button_.draw("Reset", true,  [this](){this->setConfigToDefault();});
        ImGui::SameLine();        
        this->button_.draw("Save Settings", true,  [this](){this->show_ask_for_save_ = true;});
                
        if(this->show_ask_for_save_ == true)
        {
            if(this->save_win_.draw(this->show_ask_for_save_))
            {
                this->saveConfigAsDefault();
            }
        }
 
        return changed;
    }

    void LayoutWin::setConfigToDefault()
    {   
        this->config_->show_cards = this->default_config_->show_cards;
        this->config_->show_camera_control = this->default_config_->show_camera_control;
        this->config_->show_im_proc_settings_window = this->default_config_->show_im_proc_settings_window;
        this->config_->show_card_images = this->default_config_->show_card_img;
        this->config_->show_rank_images = this->default_config_->show_rank_img;
        this->config_->show_suit_images = this->default_config_->show_suit_img;
        
        this->config_->live_image_width = this->default_config_->live_image_width;
        this->config_->live_image_height = this->default_config_->live_image_height;
        this->config_->card_image_height_percent = this->default_config_->card_image_height_percent;
        this->config_->card_rank_suit_height_percent = this->default_config_->card_rank_suit_height_percent;
        this->config_->card_outline_color = {this->default_config_->card_outline_b, this->default_config_->card_outline_g, this->default_config_->card_outline_r}; 
    }

	void LayoutWin::saveConfigAsDefault()
    {
        this->default_config_->show_cards = config_->show_cards;
        this->default_config_->show_im_proc_settings_window = config_->show_im_proc_settings_window;
        this->default_config_->show_card_img = config_->show_card_images;
        this->default_config_->show_rank_img = config_->show_rank_images;
        this->default_config_->show_suit_img = config_->show_suit_images;
        this->default_config_->show_camera_control = config_->show_camera_control;
        this->default_config_->live_image_width = config_->live_image_width;
        this->default_config_->live_image_height = config_->live_image_height;
        this->default_config_->card_outline_b = config_->card_outline_color[0];
        this->default_config_->card_outline_g = config_->card_outline_color[1];
        this->default_config_->card_outline_r = config_->card_outline_color[2];
        this->default_config_->card_image_height_percent = config_->card_image_height_percent;
        this->default_config_->card_rank_suit_height_percent= config_->card_rank_suit_height_percent;
        this->default_config_->saveConfig();
    };


} //end namespace gui