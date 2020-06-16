#include<iostream>

#include "GUI.h"

namespace gui {

    void GUI::setToDefault()
    {
        this->show_frame_ = this->default_config_->show_frame;
        this->show_main_window_ = this->default_config_->show_main_window;
        this->show_layout_window_ = this->default_config_->show_layout_window;
        this->layout_config_->show_cards = this->default_config_->show_cards;
        this->layout_config_->show_camera_control = this->default_config_->show_camera_control;
        this->layout_config_->show_im_proc_settings_window = this->default_config_->show_im_proc_settings_window;
        this->layout_config_->show_card_images = this->default_config_->show_card_img;
        this->layout_config_->show_rank_images = this->default_config_->show_rank_img;
        this->layout_config_->show_suit_images = this->default_config_->show_suit_img;
        this->layout_config_->live_image_height = this->default_config_->live_image_height;
        this->layout_config_->live_image_width = this->default_config_->live_image_width;
        this->layout_config_->card_image_height_percent = this->default_config_->card_image_height_percent;
        this->layout_config_->card_rank_suit_height_percent = this->default_config_->card_rank_suit_height_percent;
        this->layout_config_->card_outline_color = {this->default_config_->card_outline_b, this->default_config_->card_outline_g, this->default_config_->card_outline_r}; 

    }
    
    void GUI::saveAsDefault()
    {
        this->default_config_->show_frame = this->show_frame_;
        this->default_config_->show_main_window = this->show_main_window_;
        this->default_config_->show_layout_window = this->show_layout_window_;
        this->default_config_->saveConfig();
    }

    void GUI::drawGui(const cv::Mat& live_frame)
    {   
        
        // set up GUI
        this->setEventHandler();
	    this->drawGuiFrame();

        std::vector<detect::Card> cards = this->data_detect_->public_cards;
        cards.insert(cards.end(), this->data_detect_->robot_cards.begin(), this->data_detect_->robot_cards.end());

        // Add Elements to GUI
        live_view_.update( live_frame, this->layout_config_->live_image_width, this->layout_config_->live_image_height, cards, this->layout_config_->card_outline_color);
        live_view_.draw(this->show_frame_);

        if(main_win_.draw(this->show_main_window_))
        {
            this->closeWindow();
        }

        this->img_proc_settings_.draw( this->layout_config_->show_im_proc_settings_window);

        this->cam_control_changed_ = this->camera_settings_.draw( this->layout_config_->show_camera_control);

        this->layout_.draw( this->show_layout_window_);

        this->poker_game_.draw( this->show_game_window_);


        if( this->layout_config_->show_card_images)
        {
            this->card_images_.update(this->default_config_->card_aspect_ratio, this->card_image_height_, cards, this->layout_config_->card_image_height_percent);
            this->card_images_.draw(this->layout_config_->show_card_images);
        }

        if( this->layout_config_->show_rank_images)
        {
            this->rank_images_.update(this->card_rank_suit_height_, cards, this->layout_config_->card_rank_suit_height_percent);
            this->rank_images_.draw(this->layout_config_->show_rank_images);
        }

        if( this->layout_config_->show_suit_images)
        {
            this->suit_images_.update(this->card_rank_suit_height_, cards, this->layout_config_->card_rank_suit_height_percent);
            this->suit_images_.draw(this->layout_config_->show_suit_images);
        }
        
        /*if(capture_train_img_.capture_button_pressed_ || capture_train_img_.capture_)
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
        }*/

        //Render and Check if Close is called on GUI
        this->render();
		this->listenWindowClose();
    }

} // end namespace gui