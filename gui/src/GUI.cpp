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

    void GUI::drawGui(const cv::Mat& live_frame)
    {   
        
        // set up GUI
        this->setEventHandler();
	    this->drawGuiFrame();

        std::vector<detect::Card> cards = this->data_detect_->public_cards;
        cards.insert(cards.end(), this->data_detect_->robot_cards.begin(), this->data_detect_->robot_cards.end());

        // Add Elements to GUI
        live_view_.update( live_frame, this->layout_.getUserInput().live_image_width, this->layout_.getUserInput().live_image_height, cards, this->layout_.getUserInput().card_outline_color);
        live_view_.draw(this->show_frame_);

        if(main_win_.draw(this->show_main_window_))
        {
            this->closeWindow();
        }

        this->img_proc_settings_.draw(this->show_im_proc_settings_window_);
        this->data_detect_->identification_threshold = img_proc_settings_.getUserInput().identification_threshold;
        this->data_detect_->binary_threshold = img_proc_settings_.getUserInput().binary_threshold;
        this->data_detect_->live_threshold = img_proc_settings_.getUserInput().live_threshold;

        this->cam_control_changed_ = this->camera_settings_.draw(this->show_camera_control_);
        this->camera_control_->auto_exposure = this->camera_settings_.getUserInput().auto_exposure;
        this->camera_control_->auto_focus = this->camera_settings_.getUserInput().auto_focus;
        this->camera_control_->auto_wb = this->camera_settings_.getUserInput().auto_wb;
        this->camera_control_->exposure_time = this->camera_settings_.getUserInput().exposure_time;
        this->camera_control_->brightness = this->camera_settings_.getUserInput().brightness;
        this->camera_control_->focus = this->camera_settings_.getUserInput().focus;
        this->camera_control_->zoom = this->camera_settings_.getUserInput().zoom;

        this->layout_.draw(this->show_layout_window_);
        this->show_cards_ = layout_.getUserInput().show_cards;
        this->show_im_proc_settings_window_ = this->layout_.getUserInput().show_im_proc_settings_window;
        this->show_camera_control_ = this->layout_.getUserInput().show_camera_control;
        this->show_card_images_ = this->layout_.getUserInput().show_card_images;
        this->show_rank_images_ = this->layout_.getUserInput().show_rank_images;
        this->show_suit_images_ = this->layout_.getUserInput().show_suit_images;

        this->poker_game_.draw(this->show_game_window_);
        this->data_poker_->nr_of_simulation_runs = poker_game_.getUserInput().nr_sim_runs;
        this->data_poker_->nr_of_human_players = poker_game_.getUserInput().nr_of_players;


        if(this->show_card_images_)
        {
            this->card_images_.update(this->default_config_->card_aspect_ratio, this->card_image_height_, cards, this->layout_.getUserInput().card_image_height_percent);
            this->card_images_.draw(this->show_card_images_);
        }

        if(this->show_rank_images_)
        {
            this->rank_images_.update(this->card_rank_suit_height_, cards, this->layout_.getUserInput().card_rank_suit_height_percent);
            this->rank_images_.draw(this->show_rank_images_);
        }

        if(this->show_suit_images_)
        {
            this->suit_images_.update(this->card_rank_suit_height_, cards, this->layout_.getUserInput().card_rank_suit_height_percent);
            this->suit_images_.draw(this->show_suit_images_);
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