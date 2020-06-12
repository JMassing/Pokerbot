#include<iostream>

#include "GUI.h"

namespace gui {

    void GUI::setToDefault()
    {
        this->show_frame_ = this->default_config_->show_frame;
        this->show_main_window_ = this->default_config_->show_main_window;
        this->show_layout_window_ = this->default_config_->show_layout_window;
    }
    
    void GUI::saveAsDefault()
    {
        this->default_config_->show_frame = this->show_frame_;
        this->default_config_->show_main_window = this->show_main_window_;
        this->default_config_->show_layout_window = this->show_layout_window_;
        this->default_config_->saveConfig();
    }

    void GUI::drawImage(const cv::Mat& frame, const int& image_width, const int& image_height)
    {
        if(!frame.empty())
        {
            //clone original frame, as we do not want to change the underlying data as a side effect.
            cv::Mat shown_image = frame.clone();

            if(image_width != shown_image.cols || image_height != shown_image.rows )
            {
                shown_image = this->visualize_.resize(shown_image, image_width, image_height);
            }

            cv::cvtColor( shown_image, shown_image, cv::COLOR_BGR2RGBA );
            GLuint texture;
            glGenTextures( 1, &texture );
            glBindTexture( GL_TEXTURE_2D, texture );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, shown_image.cols, shown_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, shown_image.data );
            ImGui::Image( reinterpret_cast<void*>( static_cast<intptr_t>( texture ) ), ImVec2( shown_image.cols, shown_image.rows ) );
        }
        else
        {
            ImGui::Text("No Image to show");
        }
    }

    void GUI::drawCardImages(const std::vector<detect::Card>& cards)
    {
        int height = this->card_image_height_ * this->layout_.getConfig().card_image_height_percent/100;
        for(const auto& card: cards)
        {
            this->drawImage(card.card_image.image, height/this->default_config_->card_aspect_ratio, height); 
            ImGui::SameLine();  
        }
    }

    void GUI::drawRankImages(const std::vector<detect::Card>& cards)
    {
        int height = this->card_rank_suit_height_ * this->layout_.getConfig().card_rank_suit_height_percent/100;
        for(const auto& card: cards)
        {
            this->drawImage(card.rank_image.image, height, height);
            ImGui::SameLine();
        }
    }

    void GUI::drawSuitImages(const std::vector<detect::Card>& cards)
    {
        int height = this->card_rank_suit_height_ * this->layout_.getConfig().card_rank_suit_height_percent/100;
        for(const auto& card: cards)
        {
            this->drawImage(card.suit_image.image, height, height);
            ImGui::SameLine();
        }
    }

    void GUI::drawLiveView(const cv::Mat& frame, const std::vector<detect::Card>& cards)
    {		       
        
        //clone original frame, as we do not want to change the underlying data as a side effect.
        cv::Mat shown_image = frame.clone();

        if(show_cards_ && cards.size() > 0)
        {
            this->visualize_.drawCards(cards, shown_image, this->layout_.getConfig().card_outline_color);
        }

        if(this->capture_train_img_.capture_)
        {
            cv::Rect capture_train_img_area(150, 100, shown_image.cols-300, shown_image.rows-200);	
            this->visualize_.drawRectangle(shown_image, capture_train_img_area, cv::Scalar{255, 0, 0});
            capture_train_img_.printInstructions(shown_image, cv::Scalar{255, 0, 0});
        }
        if(!this->capture_train_img_.capture_)
        {
            this->visualize_.drawRectangle(shown_image, this->data_detect_->robot_area, cv::Scalar{255, 125, 0});
            this->visualize_.drawRectangle(shown_image, this->data_detect_->public_area, cv::Scalar{0, 255, 255});
        }

        this->drawImage(shown_image, this->layout_.getConfig().live_image_width,this->layout_.getConfig().live_image_height);
    }

    void GUI::drawMainWindow()
    {
        // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);  

        ImGui::InputInt("# of Opponents", &this->data_poker_->nr_of_human_players); ImGui::SameLine(); this->helpMarker("Nr of opponents playing against the bot.");  
        // make sure nr of player >= 0, otherwise program will crash
        this->enforceBoundaries(this->default_config_->min_players, this->default_config_->max_players, this->data_poker_->nr_of_human_players);
        ImGui::Text("Probability of winning = %.2f", static_cast<float>(this->data_poker_->probability.first));
        ImGui::Text("Probability of winning tie = %.2f", static_cast<float>(this->data_poker_->probability.second));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Robot Cards:");
        ImGui::SameLine();
        for(const auto& card: this->data_detect_->robot_cards)
        {   
            std::string text = this->mapping_.text_mappings.right.at(card.rank) + this->mapping_.text_mappings.right.at(card.suit);
            ImGui::Text(text.c_str());
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::Text("Public Cards:");
        ImGui::SameLine();
        for(const auto& card: this->data_detect_->public_cards)
        {   
            std::string text = this->mapping_.text_mappings.right.at(card.rank) + this->mapping_.text_mappings.right.at(card.suit);
            ImGui::Text(text.c_str());
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::Checkbox("Show Layout Settings", &this->show_layout_window_);
        this->addButton("Quit Program", [this](){this->closeWindow();});
    }

    void GUI::drawImageProcSettingsWindow()
    {
        // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -15);  

        ImGui::SliderInt("Card Threshold", &this->data_detect_->live_threshold, this->default_config_->min_live_th, this->default_config_->max_live_th); 
        ImGui::SameLine(); this->helpMarker("Threshold for detecting cards in live image. CTRL+click to input value.");  
        this->enforceBoundaries(this->default_config_->min_live_th, this->default_config_->max_live_th, this->data_detect_->live_threshold);

        ImGui::SliderInt("Rank/Suit Threshold", &this->data_detect_->identification_threshold, this->default_config_->min_bin_th, this->default_config_->max_bin_th); 
        ImGui::SameLine(); this->helpMarker("Threshold for detecting rank and suit image in upper left corner of card. CTRL+click to input value.");  
        this->enforceBoundaries( this->default_config_->min_bin_th, this->default_config_->max_bin_th, this->data_detect_->identification_threshold);

        ImGui::SliderInt("Binarization Threshold", &this->data_detect_->binary_threshold, this->default_config_->min_ident_th, this->default_config_->max_ident_th); 
        ImGui::SameLine(); this->helpMarker("Threshold for binarizing detected rank and suit images. CTRL+click to input value.");  
        this->enforceBoundaries( this->default_config_->min_ident_th, this->default_config_->max_ident_th, this->data_detect_->binary_threshold);

        ImGui::SliderInt("# of simulation runs", &this->data_poker_->nr_of_simulation_runs, this->default_config_->min_sim_runs, this->default_config_->max_sim_runs);
        ImGui::SameLine(); this->helpMarker("Nr of times the simulation is run. CTRL+click to input value.");  
        this->enforceBoundaries( this->default_config_->min_sim_runs, this->default_config_->max_sim_runs, this->data_poker_->nr_of_simulation_runs);

        this->addButton("Reset", [this](){this->data_detect_->setToDefault(); this->data_poker_->setToDefault();}); 
        ImGui::SameLine();
        bool save = false;
        this->addButton("Save Settings", [this](){this->show_ask_for_save_im_proc_ = true;}); 
        if(this->show_ask_for_save_im_proc_ == true)
        {
            this->addWindow("##saveSettingsImProc",this->show_ask_for_save_im_proc_,[this, &save](){this->askForSave(save, this->show_ask_for_save_im_proc_, "image processing");});
        }
        if(save == true)
        {
          this->data_detect_->saveAsDefault(); this->data_poker_->saveAsDefault();
        }
        this->addButton("Capture Training Images", [this](){this->capture_train_img_.captureRequested();});
    }

    void GUI::askForSave(bool& save, bool& show, std::string type)
    {
        std::string text = "Save current " + type + " settings as default?\n" 
                            + "Config.ini will be overwritten.";
        ImGui::Text(text.c_str());
        this->addButton("Yes", [&show, &save](){save = true; show = false;}); ImGui::SameLine();
        this->addButton("No", [&show](){show = false;});
    }

    void GUI::drawCameraControl()
    {
        // Give a Constant label width, the rest goes to widget size, e.g. width of slider bar
        ImGui::PushItemWidth(ImGui::GetFontSize() * -8);  

        bool changed = false;
        // draw Gui Controls and check if any control was changed. If so, set this->cam_control_changes to true, else to false
        changed |= ImGui::Checkbox("Use Auto Focus", &this->camera_control_->auto_focus); 
        changed |= ImGui::Checkbox("Use Auto Exposure", &this->camera_control_->auto_exposure);
        changed |= ImGui::Checkbox("Use Auto White Balance", &this->camera_control_->auto_wb); 
        changed |= ImGui::SliderInt("Exposure", &this->camera_control_->exposure_time, this->default_config_->min_exp_time, this->default_config_->max_exp_time);
        ImGui::SameLine(); this->helpMarker("CTRL+click to input value. Value should be negative."); 
        this->enforceBoundaries( this->default_config_->min_exp_time, this->default_config_->max_exp_time, this->camera_control_->exposure_time);

        changed |= ImGui::SliderInt("Focus", &this->camera_control_->focus, this->default_config_->min_focus, this->default_config_->max_focus); 
        ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
        this->enforceBoundaries( this->default_config_->min_focus, this->default_config_->max_focus, this->camera_control_->focus);

        changed |= ImGui::SliderInt("Brightness", &this->camera_control_->brightness, this->default_config_->min_brightness, this->default_config_->max_brightness); 
        ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");
        this->enforceBoundaries( this->default_config_->min_brightness, this->default_config_->max_brightness, this->camera_control_->brightness);

        changed |= this->addButton("Reset", [this](){this->camera_control_->setToDefault();});
        ImGui::SameLine();

        bool save = false;
        this->addButton("Save Camera Setting", [this](){this->show_ask_for_save_camera_= true;}); 
        if(this->show_ask_for_save_camera_ == true)
        {
            this->addWindow("##saveSettingsCamera",this->show_ask_for_save_camera_,[this, &save](){this->askForSave(save, this->show_ask_for_save_camera_, "camera");});
        }
        if(save == true)
        {
          this->camera_control_->saveAsDefault();
        }

        if (changed)
        {
            this->cam_control_changed_ = true;
        }
        else
        {
            this->cam_control_changed_ = false;
        }
    }

    void GUI::drawGui(const cv::Mat& frame)
    {   
        
        // set up GUI
        this->setEventHandler();
	    this->drawGuiFrame();

        std::vector<detect::Card> cards = this->data_detect_->public_cards;
        cards.insert(cards.end(), this->data_detect_->robot_cards.begin(), this->data_detect_->robot_cards.end());

        // Add Elements to GUI
        this->addWindow("Live Image", this->show_frame_, [this, &frame, &cards](){this->drawLiveView(frame, cards);}, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
        this->addWindow("Main Window", this->show_main_window_, [this](){this->drawMainWindow();});
        this->addWindow("Image Processing Settings", this->show_im_proc_settings_window_, [this](){this->drawImageProcSettingsWindow();});
        this->addWindow("Camera Controls", this->show_camera_control_, [this](){this->drawCameraControl();});

        this->layout_.draw(this->show_layout_window_);
        this->show_cards_ = layout_.getConfig().show_cards;
        this->show_im_proc_settings_window_ = this->layout_.getConfig().show_im_proc_settings_window;
        this->show_camera_control_ = this->layout_.getConfig().show_camera_control;
        this->show_card_images_ = this->layout_.getConfig().show_card_images;
        this->show_rank_images_ = this->layout_.getConfig().show_rank_images;
        this->show_suit_images_ = this->layout_.getConfig().show_suit_images;

        if(this->show_card_images_)
        {
            this->addWindow("Detected Cards", this->show_card_images_, [this, &cards](){this->drawCardImages(cards);}, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
        }

        if(this->show_rank_images_)
        {
            this->addWindow("Binarized Ranks", this->show_rank_images_, [this, &cards](){this->drawRankImages(cards);}, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
        }

        if(this->show_suit_images_)
        {
            this->addWindow("Binarized Suits", this->show_suit_images_, [this, &cards](){this->drawSuitImages(cards);}, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);
        }
        
        if(capture_train_img_.capture_button_pressed_ || capture_train_img_.capture_)
        {
            capture_train_img_.drawTrainImagesGuiWindow();
            if(capture_train_img_.capture_)
            {
                this->show_card_images_ = true;
                this->show_rank_images_ = true;
                this->show_suit_images_ = true;
                this->capture_train_img_.nr_of_cards_ = cards.size();
                if(cards.size() > 0)
                {
                    if(this->capture_train_img_.type_ == "rank")
                    {
                        this->capture_train_img_.setTrainImage(cards[0].rank_image.image);
                    }
                    else
                    {
                        this->capture_train_img_.setTrainImage(cards[0].suit_image.image);
                    }
                } 
            }
        }

        //Render and Check if Close is called on GUI
        this->render();
		this->listenWindowClose();
    }

} // end namespace gui