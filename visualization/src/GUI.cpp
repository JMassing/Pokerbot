#include<iostream>

#include "GUI.h"

namespace visualization {

    void GUI::drawImage(const cv::Mat& frame, const int& image_width, const int& image_height)
    {
        if(!frame.empty())
        {
            //clone original frame, as we do not want to change it
            cv::Mat shown_image = frame.clone();

            if(image_width != shown_image.cols || image_height != shown_image.rows )
            {
                shown_image = this->visualize_.resize(shown_image, image_width, image_height);
            }

            if(this->capture_train_img_.capture_)
            {
                this->visualize_.drawRectangle(shown_image, cv::Point(150,100), this->live_image_width_-300, this->live_image_height_-200);
                capture_train_img_.printInstructions(shown_image);
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
            this->drawImage(card.card_image, card.card_image.cols/3, card.card_image.rows/3); 
            ImGui::SameLine();
        }
    }

    void GUI::drawRankImages(const std::vector<detect::Card>& cards)
    {
        for(const auto& card: cards)
        {
            this->drawImage(card.rank_image, card.rank_image.cols/2, card.rank_image.rows/2);
            ImGui::SameLine();
        }
    }

    void GUI::drawSuitImages(const std::vector<detect::Card>& cards)
    {
        for(const auto& card: cards)
        {
            this->drawImage(card.suit_image, card.suit_image.cols/2, card.suit_image.rows/2);
            ImGui::SameLine();
        }
    }

    void GUI::drawLiveView(const cv::Mat& frame, const std::vector<detect::Card>& cards)
    {		       
        cv::Mat image = frame.clone();
        if(show_cards_ && cards.size() > 0)
        {
            this->visualize_.drawCards(cards, image);
        }

        this->drawImage(image, this->live_image_width_, this->live_image_height_);

    }

    void GUI::drawMainWindow(const std::pair<double,double>& probability, const std::vector<detect::Card>& robot_cards, const std::vector<detect::Card>& public_cards)
    {
        ImGui::Text("Probability of winning = %.2f", static_cast<float>(probability.first));
        ImGui::Text("Probability of winning tie = %.2f", static_cast<float>(probability.second));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Robot Cards:");
        ImGui::SameLine();
        for(const auto& card: robot_cards)
        {   
            std::string text = this->mapping_.text_mappings.right.at(card.rank) + this->mapping_.text_mappings.right.at(card.suit) + " ";
            ImGui::Text(text.c_str());
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::Text("Public Cards:");
        ImGui::SameLine();
        for(const auto& card: public_cards)
        {   
            std::string text = this->mapping_.text_mappings.right.at(card.rank) + this->mapping_.text_mappings.right.at(card.suit) + " ";
            ImGui::Text(text.c_str());
            ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::Checkbox("Show Cards", &this->show_cards_);
        ImGui::Checkbox("Show Developer View", &this->show_developer_window_);  
        this->addButton("Quit", [this](){this->closeWindow();});
    }

    void GUI::drawDeveloperWindow(int& live_threshold)
    {
        ImGui::SliderInt("threshold", &live_threshold, 0, 200);  
        ImGui::Checkbox("Show Card Images", &this->show_card_images_);
        ImGui::Checkbox("Show Rank Images", &this->show_rank_images_);
        ImGui::Checkbox("Show Suit Images", &this->show_suit_images_);
        this->addButton("Capture Training Images", [this](){this->capture_train_img_.captureRequested();});
    }

    
    void GUI::drawGui(const cv::Mat& frame, const std::vector<detect::Card>& robot_cards, const std::vector<detect::Card>& public_cards, const std::pair<double,double>& probability, int& live_threshold)
    {   
        
        // set up GUI
        this->setEventHandler();
	    this->drawGuiFrame();

        std::vector<detect::Card> cards = public_cards;
        cards.insert(cards.end(), robot_cards.begin(), robot_cards.end());

        // Add Elements to GUI
        this->addWindow("Live Image", this->show_frame_, [this, &frame, &cards](){this->drawLiveView(frame, cards);});
        this->addWindow("Main Window", this->show_main_window_, [this, &probability, &robot_cards, &public_cards](){this->drawMainWindow(probability, robot_cards, public_cards);});
        this->addWindow("Developer Mode", this->show_developer_window_, [this, &live_threshold](){this->drawDeveloperWindow(live_threshold);});

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