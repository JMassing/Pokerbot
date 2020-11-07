#include "SettingsWin.hpp"        

namespace gui
{

    void SettingsWin::draw()
    {
        this->input_ = false;
        this->game_settings_.stop_game = false;
        this->game_settings_.start_game = false;
      
        if(this->show_)
        {
            ImGui::Begin(this->name_.c_str(), &this->show_, this->flag_);

            // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
            ImGui::PushItemWidth(ImGui::GetFontSize() * -15);  

            // Game Settings
            ImGui::Text("Game Settings:");
            this->input_ |= ImGui::Checkbox("Mask Robot Cards", &this->layout_settings_.mask_robot_cards);
            this->input_ |= ImGui::Checkbox("Show Probability", &this->layout_settings_.show_probability);
            this->input_ |= ImGui::Checkbox("Show Robot Hand", &this->layout_settings_.show_robot_hand);
            
            // preparation for making it possible to play with multiple human players. Right now deactivated
            // as side pots are not implemented yet.

            /*this->input_ |= this->input_field_.draw(
                "# of Opponents", 
                this->min_players_, 
                this->max_players_, 
                this->game_settings_.nr_of_human_players, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Nr of opponents playing against the bot."); */ 

            this->input_ |= this->slider_.draw(
                "# of simulation runs", 
                this->min_sim_runs_, 
                this->max_sim_runs_, 
                this->game_settings_.nr_of_simulation_runs, 
                true
            );

            this->input_ |= this->button_.draw(
                "Start Game", !this->game_settings_.playing_game,
                [this](){this->game_settings_.start_game = true;
                this->game_settings_.playing_game = true;}
            ); ImGui::SameLine();
            this->input_ |= this->button_.draw(
                "Stop Game", this->game_settings_.playing_game, 
                [this](){this->game_settings_.stop_game = true;
                this->game_settings_.playing_game = false;}
            ); 
            ImGui::NewLine();    
            // Layout
            ImGui::Text("Live View Settings:");

            ImVec4 tmp_card_outline_color = 
                ImVec4( 
                    static_cast<float>(this->layout_settings_.card_outline_color[2])/255.0f, 
                    static_cast<float>(this->layout_settings_.card_outline_color[1])/255.0f, 
                    static_cast<float>(this->layout_settings_.card_outline_color[0])/255.0f, 1.00f
                );

            this->input_ |= ImGui::ColorEdit3("card outline color", (float*)&tmp_card_outline_color);

            this->layout_settings_.card_outline_color = 
                {
                    tmp_card_outline_color.z*255.0f, 
                    tmp_card_outline_color.y*255.0f, 
                    tmp_card_outline_color.x*255.0f
                };
        
            if (ImGui::CollapsingHeader("Live View Size"))
            {
                this->input_ |= this->button_.draw(
                    "800x600", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 800; 
                        this->layout_settings_.live_view_height = 600;
                    }
                ); ImGui::SameLine();    

                this->input_ |= this->button_.draw(
                    "1024x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1024; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1280x720", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280; 
                        this->layout_settings_.live_view_height = 720;
                    }
                );

                this->input_ |= this->button_.draw(
                    "1280x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1280x800", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280; 
                        this->layout_settings_.live_view_height = 800;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1280x1024", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1280;
                        this->layout_settings_.live_view_height = 1024;
                    }
                );

                this->input_ |= this->button_.draw(
                    "1360x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1360; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1366x768", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1366; 
                        this->layout_settings_.live_view_height = 768;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1400x1050", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1400; 
                        this->layout_settings_.live_view_height = 1050;
                    }
                ); 

                this->input_ |= this->button_.draw(
                    "1440x900", 
                    true,  
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1440; 
                        this->layout_settings_.live_view_height = 900;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1600x900", 
                    true, 
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1600; 
                        this->layout_settings_.live_view_height = 900;
                    }
                ); ImGui::SameLine();

                this->input_ |= this->button_.draw(
                    "1920x1080", 
                    true, 
                    [this]()
                    {
                        this->layout_settings_.live_view_width = 1920; 
                        this->layout_settings_.live_view_height = 1080;
                    }
                ); 
            }

            this->input_ |= this->slider_.draw(
                "Card Image Size",
                this->min_card_image_height_percent_, 
                this->max_card_image_height_percent_, 
                this->layout_settings_.card_image_height_percent,
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Size of displayed card images in %. CTRL+click to input value.");

            this->input_ |= this->slider_.draw(
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
            this->input_ |= ImGui::Checkbox("Use Auto Focus", &this->camera_settings_.auto_focus); 
            this->input_ |= ImGui::Checkbox("Use Auto Exposure", &this->camera_settings_.auto_exposure);
            this->input_ |= ImGui::Checkbox("Use Auto White Balance", &this->camera_settings_.auto_wb); 

            this->input_ |= this->slider_.draw(
                "Exposure", 
                this->min_exp_time_, 
                this->max_exp_time_, 
                this->camera_settings_.exposure_time, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value. Value should be negative."); 

            this->input_ |= this->slider_.draw(
                "Focus", 
                this->min_focus_, 
                this->max_focus_, 
                this->camera_settings_.focus, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value.");

            this->input_ |= this->slider_.draw(
                "Brightness", 
                this->min_brightness_, 
                this->max_brightness_, 
                this->camera_settings_.brightness, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value.");

            this->input_ |= this->slider_.draw(
                "WB Temperature", 
                this->min_wb_temp_, 
                this->max_wb_temp_, 
                this->camera_settings_.wb_temperature, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("CTRL+click to input value.");

            // Image Processing
            ImGui::NewLine();
            ImGui::Text("Image Processing Settings:");

            this->input_ |= this->slider_.draw(
                "Card Threshold", 
                this->min_live_th_, 
                this->max_live_th_, 
                this->proc_settings_.live_threshold, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Threshold for detecting cards in live image. CTRL+click to input value.");  

            this->input_ |= this->slider_.draw(
                "Rank/Suit Threshold",  
                this->min_bin_th_, 
                this->max_bin_th_, 
                this->proc_settings_.identification_threshold, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Threshold for detecting rank and suit image in upper left corner of card. CTRL+click to input value.");  

            this->input_ |= this->slider_.draw(
                "Binarization Threshold", 
                this->min_ident_th_, 
                this->max_ident_th_, 
                this->proc_settings_.binary_threshold, 
                true
            ); ImGui::SameLine(); 
            this->helpMarker("Threshold for binarizing detected rank and suit images. CTRL+click to input value.");  
              
            ImGui::NewLine();
            // Reset buttons
            this->input_ |= this->button_.draw(
                "Reset Settings", true, [this](){this->setConfigToDefault();}
            ); ImGui::SameLine();
            
            this->button_.draw(
                "Save Settings", true, [this](){this->show_ask_for_save_ = true;}
            ); 
            
            AskForSaveWin save_win("Save as default", show_ask_for_save_); 
            // Check if settings should be saved as new default
            if(this->show_ask_for_save_ == true)
            {
                save_win.draw();
            }
            if(save_win.save_ == true)
            {
               this->saveConfigAsDefault();
            }
          
        }

        ImGui::End();
    }

    void SettingsWin::setConfigToDefault()
    {
        this->camera_settings_.setToDefault(this->default_config_);
        this->proc_settings_.setToDefault(this->default_config_);
        this->game_settings_.setToDefault(this->default_config_);
        this->layout_settings_.setToDefault(this->default_config_);
    }

	void SettingsWin::saveConfigAsDefault()
    {
        // camera settings
        this->default_config_.auto_exposure = this->camera_settings_.auto_exposure;
        this->default_config_.auto_focus = this->camera_settings_.auto_focus;
        this->default_config_.auto_wb = this->camera_settings_.auto_wb;
        this->default_config_.exposure_time = this->camera_settings_.exposure_time;
        this->default_config_.brightness = this->camera_settings_.brightness;
        this->default_config_.focus = this->camera_settings_.focus;
        this->default_config_.zoom = this->camera_settings_.zoom;
        this->default_config_.image_height = this->camera_settings_.image_height;
        this->default_config_.image_width = this->camera_settings_.image_width; 

        // image processing settings
        this->default_config_.live_threshold = this->proc_settings_.live_threshold;
        this->default_config_.binary_threshold = this->proc_settings_.binary_threshold;
        this->default_config_.identification_threshold = this->proc_settings_.identification_threshold;

        // poker simulation settings
        this->default_config_.nr_sim_runs = this->game_settings_.nr_of_simulation_runs;
        this->default_config_.nr_opponents = this->game_settings_.nr_of_human_players;
        
        this->default_config_.saveConfig();
    };


} //end namespace gui