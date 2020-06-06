#include<iostream>

#include "GUI.h"

namespace visualization {

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
        for(const auto& card: cards)
        {
            this->drawImage(card.card_image, card.card_image.cols/4, card.card_image.rows/4); 
            ImGui::SameLine();
        }
    }

    void GUI::drawRankImages(const std::vector<detect::Card>& cards)
    {
        for(const auto& card: cards)
        {
            this->drawImage(card.rank_image, card.rank_image.cols/3, card.rank_image.rows/3);
            ImGui::SameLine();
        }
    }

    void GUI::drawSuitImages(const std::vector<detect::Card>& cards)
    {
        for(const auto& card: cards)
        {
            this->drawImage(card.suit_image, card.suit_image.cols/3, card.suit_image.rows/3);
            ImGui::SameLine();
        }
    }

    void GUI::drawLiveView(const cv::Mat& frame, const std::vector<detect::Card>& cards)
    {		       
        
        //clone original frame, as we do not want to change the underlying data as a side effect.
        cv::Mat shown_image = frame.clone();

        if(show_cards_ && cards.size() > 0)
        {
            this->visualize_.drawCards(cards, shown_image, cv::Scalar{255, 0, 0});
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

        //detect::ImProc::binarizeImage(shown_image, shown_image, this->data_detect_->live_threshold, cv::THRESH_BINARY);

        this->drawImage(shown_image, this->live_image_width_, this->live_image_height_);
    }

    void GUI::drawMainWindow()
    {
        
        ImGui::SliderInt("# of Opponents", &this->data_poker_->nr_of_human_players, 1, 9);  ImGui::SameLine(); this->helpMarker("Nr of opponents playing against the bot. CTRL+click to input value.");  
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
        ImGui::Checkbox("Show Cards", &this->show_cards_);
        ImGui::Checkbox("Show Camera Controls", &this->show_camera_control_);
        ImGui::Checkbox("Show Developer View", &this->show_developer_window_);  
        this->addButton("Quit Program", [this](){this->closeWindow();});
    }

    void GUI::drawDeveloperWindow()
    {
        ImGui::SliderInt("Card Threshold", &this->data_detect_->live_threshold, 0, 255); ImGui::SameLine(); this->helpMarker("Threshold for detecting cards in live image. CTRL+click to input value.");  
        ImGui::SliderInt("Rank/Suit Threshold", &this->data_detect_->identification_threshold, 0, 255); ImGui::SameLine(); this->helpMarker("Threshold for detecting rank and suit image in upper left corner of card. CTRL+click to input value.");  
        ImGui::SliderInt("Binarization Threshold", &this->data_detect_->binary_threshold, 0, 255); ImGui::SameLine(); this->helpMarker("Threshold for binarizing detected rank and suit images. CTRL+click to input value.");  
        ImGui::SliderInt("# of simulation runs", &this->data_poker_->nr_of_simulation_runs, 0, 100000); ImGui::SameLine(); this->helpMarker("Nr of times the simulation is run. CTRL+click to input value.");  
        ImGui::Checkbox("Show Card Images", &this->show_card_images_);
        ImGui::Checkbox("Show Rank Images", &this->show_rank_images_);
        ImGui::Checkbox("Show Suit Images", &this->show_suit_images_);
        this->addButton("Capture Training Images", [this](){this->capture_train_img_.captureRequested();});
    }

    void GUI::drawCameraControl()
    {
        ImGui::Checkbox("Use Auto Focus", &this->camera_control_->auto_focus);
        ImGui::Checkbox("Use Auto Exposure", &this->camera_control_->auto_exposure);
        ImGui::Checkbox("Use Auto White Balance", &this->camera_control_->auto_wb);
        ImGui::SliderInt("Exposure", &this->camera_control_->exposure_time, -12, -1); ImGui::SameLine(); this->helpMarker("CTRL+click to input value. Value should be negative.");  
        ImGui::SliderInt("Focus", &this->camera_control_->focus, 0, 250); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");  
        ImGui::SliderInt("Brightness", &this->camera_control_->brightness, 0, 255); ImGui::SameLine(); this->helpMarker("CTRL+click to input value.");  
    }

    void GUI::drawGui(const cv::Mat& frame)
    {   
        
        // set up GUI
        this->setEventHandler();
	    this->drawGuiFrame();

        std::vector<detect::Card> cards = this->data_detect_->public_cards;
        cards.insert(cards.end(), this->data_detect_->robot_cards.begin(), this->data_detect_->robot_cards.end());

        // Add Elements to GUI
        this->addWindow("Live Image", this->show_frame_, [this, &frame, &cards](){this->drawLiveView(frame, cards);});
        this->addWindow("Main Window", this->show_main_window_, [this](){this->drawMainWindow();});
        this->addWindow("Developer Mode", this->show_developer_window_, [this](){this->drawDeveloperWindow();});
        this->addWindow("Camera Controls", this->show_camera_control_, [this](){this->drawCameraControl();});

        if(this->show_card_images_)
        {
            this->addWindow("Detected Cards", this->show_card_images_, [this, &cards](){this->drawCardImages(cards);});
        }

        if(this->show_rank_images_)
        {
            this->addWindow("Binarized Ranks", this->show_rank_images_, [this, &cards](){this->drawRankImages(cards);});
        }

        if(this->show_suit_images_)
        {
            this->addWindow("Binarized Suits", this->show_suit_images_, [this, &cards](){this->drawSuitImages(cards);});
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
                        this->capture_train_img_.setTrainImage(cards[0].rank_image);
                    }
                    else
                    {
                        this->capture_train_img_.setTrainImage(cards[0].suit_image);
                    }
                } 
            }
        }

        //Render and Check if Close is called on GUI
        this->render();
		this->listenWindowClose();
    }

} // end namespace visualization