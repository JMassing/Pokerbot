#include "LayoutWin.h"        

namespace gui
{

    bool LayoutWin::content()
    {
        bool changed = false;
        // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -14);  

        changed |= ImGui::Checkbox("Show Card Outline", &this->config_.show_cards);ImGui::SameLine(); this->helpMarker("If checked, outline of cards and cards rank/suit are displayed in the live image.");  
        ImVec4 tmp_card_outline_color = ImVec4(static_cast<float>(this->config_.card_outline_color[2])/255.0f, 
                                               static_cast<float>(this->config_.card_outline_color[1])/255.0f, 
                                               static_cast<float>(this->config_.card_outline_color[0])/255.0f, 1.00f);
        changed |= ImGui::ColorEdit3("card outline color", (float*)&tmp_card_outline_color);
        this->config_.card_outline_color = {tmp_card_outline_color.z*255.0f, tmp_card_outline_color.y*255.0f, tmp_card_outline_color.x*255.0f};
        changed |= ImGui::Checkbox("Show Camera Controls", &this->config_.show_camera_control);
        changed |= ImGui::Checkbox("Show Image Processing Settings", &this->config_.show_im_proc_settings_window);
        changed |= ImGui::Checkbox("Show Card Images", &this->config_.show_card_images); ImGui::SameLine(); this->helpMarker("If checked, card images extracted from live frame are displayed.");
        changed |= ImGui::Checkbox("Show Rank Images", &this->config_.show_rank_images); ImGui::SameLine(); this->helpMarker("If checked, binarized rank images extracted from card images are displayed.");
        changed |= ImGui::Checkbox("Show Suit Images", &this->config_.show_suit_images); ImGui::SameLine(); this->helpMarker("If checked, binarized suit images extracted from card images are displayed.");
        if (ImGui::CollapsingHeader("Live Image Size"))
        {
            this->addButton("800x600", [this](){this->config_.live_image_width = 800; this->config_.live_image_height = 600;}); ImGui::SameLine();
            this->addButton("1024x768", [this](){this->config_.live_image_width = 1024; this->config_.live_image_height = 768;}); ImGui::SameLine();
            this->addButton("1280x720", [this](){this->config_.live_image_width = 1280; this->config_.live_image_height = 720;}); 
            this->addButton("1280x768", [this](){this->config_.live_image_width = 1280; this->config_.live_image_height = 768;}); ImGui::SameLine();
            this->addButton("1280x800", [this](){this->config_.live_image_width = 1280; this->config_.live_image_height = 800;}); ImGui::SameLine();
            this->addButton("1280x1024", [this](){this->config_.live_image_width = 1280; this->config_.live_image_height = 1024;});
            this->addButton("1360x768", [this](){this->config_.live_image_width = 1360; this->config_.live_image_height = 768;}); ImGui::SameLine();
            this->addButton("1366x768", [this](){this->config_.live_image_width = 1366; this->config_.live_image_height = 768;}); ImGui::SameLine();
            this->addButton("1400x1050", [this](){this->config_.live_image_width = 1400; this->config_.live_image_height = 1050;});
            this->addButton("1440x900", [this](){this->config_.live_image_width = 1440; this->config_.live_image_height = 900;}); ImGui::SameLine();
            this->addButton("1600x900", [this](){this->config_.live_image_width = 1600; this->config_.live_image_height = 900;}); ImGui::SameLine();
            this->addButton("1920x1080", [this](){this->config_.live_image_width = 1920; this->config_.live_image_height = 1080;});
        }
        changed |= ImGui::SliderInt("Card Image Size", &this->config_.card_image_height_percent, 25, 175); ImGui::SameLine(); this->helpMarker("Size of displayed card images in %. CTRL+click to input value.");
        this->enforceBoundaries(25, 175, this->config_.card_image_height_percent);
        changed |= ImGui::SliderInt("Rank/Suit Image Size", &this->config_.card_rank_suit_height_percent, 25, 175);ImGui::SameLine(); this->helpMarker("Size of displayed rank and suit images in %. CTRL+click to input value.");
        this->enforceBoundaries(25, 175, this->config_.card_rank_suit_height_percent);

        this->addButton("Reset Layout", [this](){this->setConfigToDefault();}); 
        ImGui::SameLine();        
        this->addButton("Save Layout", [this](){this->show_ask_for_save_ = true;}); 
        
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
        config_.show_cards = this->default_config_->show_cards;
        config_.show_camera_control = this->default_config_->show_camera_control;
        config_.show_im_proc_settings_window = this->default_config_->show_im_proc_settings_window;
        config_.show_card_images = this->default_config_->show_card_img;
        config_.show_rank_images = this->default_config_->show_rank_img;
        config_.show_suit_images = this->default_config_->show_suit_img;
        
        config_.live_image_width = this->default_config_->live_image_width;
        config_.live_image_height = this->default_config_->live_image_height;
        config_.card_image_height_percent = this->default_config_->card_image_height_percent;
        config_.card_rank_suit_height_percent = this->default_config_->card_rank_suit_height_percent;
        config_.card_outline_color = {this->default_config_->card_outline_b, this->default_config_->card_outline_g, this->default_config_->card_outline_r}; 
    }

	void LayoutWin::saveConfigAsDefault()
    {
        this->default_config_->show_cards = config_.show_cards;
        this->default_config_->show_im_proc_settings_window = config_.show_im_proc_settings_window;
        this->default_config_->show_card_img = config_.show_card_images;
        this->default_config_->show_rank_img = config_.show_rank_images;
        this->default_config_->show_suit_img = config_.show_suit_images;
        this->default_config_->show_camera_control = config_.show_camera_control;
        this->default_config_->live_image_width = config_.live_image_width;
        this->default_config_->live_image_height = config_.live_image_height;
        this->default_config_->card_outline_b = config_.card_outline_color[0];
        this->default_config_->card_outline_g = config_.card_outline_color[1];
        this->default_config_->card_outline_r = config_.card_outline_color[2];
        this->default_config_->card_image_height_percent = config_.card_image_height_percent;
        this->default_config_->card_rank_suit_height_percent= config_.card_rank_suit_height_percent;
        this->default_config_->saveConfig();
    };


} //end namespace gui