#include "SettingsWin.hpp"        

namespace gui
{

    bool SettingsWin::draw()
    {
        bool changed = false;

        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
            ImGui::PushItemWidth(ImGui::GetFontSize() * -15);  

            // Layout
            ImGui::Text("Live View Settings:");

            ImVec4 tmp_card_outline_color = 
                ImVec4( 
                    static_cast<float>(this->layout_settings_.card_outline_color[2])/255.0f, 
                    static_cast<float>(this->layout_settings_.card_outline_color[1])/255.0f, 
                    static_cast<float>(this->layout_settings_.card_outline_color[0])/255.0f, 1.00f
                );

            changed |= ImGui::ColorEdit3("card outline color", (float*)&tmp_card_outline_color);

            this->layout_settings_.card_outline_color = 
                {
                    tmp_card_outline_color.z*255.0f, 
                    tmp_card_outline_color.y*255.0f, 
                    tmp_card_outline_color.x*255.0f
                };
        
            if (ImGui::CollapsingHeader("Live View Size"))
            {
                changed |= this->button_.draw(
                    "800x600", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 800; 
                        this->layout_settings_.live_view_height = 600;
                    }
                ); ImGui::SameLine();    

                changed |= this->button_.draw(
                    "1024x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1024; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1280x720", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280; 
                        this->layout_settings_.live_view_height = 720;
                    }
                );

                changed |= this->button_.draw(
                    "1280x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1280x800", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280; 
                        this->layout_settings_.live_view_height = 800;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1280x1024", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280;
                        this->layout_settings_.live_view_height = 1024;
                    }
                );

                changed |= this->button_.draw(
                    "1360x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1360; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1366x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1366; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1400x1050", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1400; 
                        this->layout_settings_.live_view_height = 1050;
                    }
                ); 

                changed |= this->button_.draw(
                    "1440x900", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1440; 
                        this->layout_settings_.live_view_height = 900;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1600x900", 
                    true, 
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1600; 
                        this->layout_settings_.live_view_height = 900;
                    }
                ); ImGui::SameLine();

                changed |= this->button_.draw(
                    "1920x1080", 
                    true, 
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1920; 
                        this->layout_settings_.live_view_height = 1080;
                    }
                ); 
            }

            changed |= this->slider_.draw(
                "Card Image Size",
                this->min_card_image_height_percent_, 
                this->max_card_image_height_percent_, 
                this->layout_settings_.card_image_height_percent,
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Size of displayed card images in %. CTRL+click to input value.");

            changed |= this->slider_.draw(
                "Rank/Suit Image Size", 
                this->min_rank_suit_image_height_percent_, 
                this->max_rank_suit_image_height_percent_, 
                this->layout_settings_.card_rank_suit_height_percent, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Size of displayed rank and suit images in %. CTRL+click to input value.");

            // Camera Controls
            ImGui::NewLine();
            ImGui::Text("Camera Settings:");
            changed |= ImGui::Checkbox("Use Auto Focus", &this->camera_settings_.auto_focus); 
            changed |= ImGui::Checkbox("Use Auto Exposure", &this->camera_settings_.auto_exposure);
            changed |= ImGui::Checkbox("Use Auto White Balance", &this->camera_settings_.auto_wb); 

            changed |= this->slider_.draw(
                "Exposure", 
                this->min_exp_time_, 
                this->max_exp_time_, 
                this->camera_settings_.exposure_time, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value. Value should be negative."); 

            changed |= this->slider_.draw(
                "Focus", 
                this->min_focus_, 
                this->max_focus_, 
                this->camera_settings_.focus, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value.");

            changed |= this->slider_.draw(
                "Brightness", 
                this->min_brightness_, 
                this->max_brightness_, 
                this->camera_settings_.brightness, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value.");

            // Image Processing
            ImGui::NewLine();
            ImGui::Text("Image Processing Settings:");

            changed |= this->slider_.draw(
                "Card Threshold", 
                this->min_live_th_, 
                this->max_live_th_, 
                this->proc_settings_.live_threshold, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Threshold for detecting cards in live image. CTRL+click to input value.");  

            changed |= this->slider_.draw(
                "Rank/Suit Threshold",  
                this->min_bin_th_, 
                this->max_bin_th_, 
                this->proc_settings_.identification_threshold, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Threshold for detecting rank and suit image in upper left corner of card. CTRL+click to input value.");  

            changed |= this->slider_.draw(
                "Binarization Threshold", 
                this->min_ident_th_, 
                this->max_ident_th_, 
                this->proc_settings_.binary_threshold, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Threshold for binarizing detected rank and suit images. CTRL+click to input value.");  


            // Poker Simulation
            ImGui::NewLine();
            ImGui::Text("Poker Simulation Settings:");
            changed |= this->input_.draw(
                "# of Opponents", 
                this->min_players_, 
                this->max_players_, 
                this->nr_of_human_players_, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Nr of opponents playing against the bot.");  

            changed |= this->slider_.draw(
                "# of simulation runs", 
                this->min_sim_runs_, 
                this->max_sim_runs_, 
                this->nr_of_simulation_runs_, 
                true
            );

            changed |= this->button_.draw(
                "Reset", true, [this](){this->setConfigToDefault();}
            ); ImGui::SameLine();
            
            this->button_.draw(
                "Save Settings", true, [this](){this->show_ask_for_save_ = true;}
            ); 

        }

        ImGui::End();

        return changed;
    }

    void SettingsWin::setConfigToDefault()
    {}

	void SettingsWin::saveConfigAsDefault()
    {};


} //end namespace gui