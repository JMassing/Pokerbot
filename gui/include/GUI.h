#pragma once

#include <utility>
#include <vector>
#include <memory>

#include <opencv2/core.hpp>

#include "Card.h"
#include "DataDetectGui.h"
#include "DataPokerGui.h"
#include "CameraControls.h"
#include "ImProc.h"
#include "DefaultConfig.h"
#include "LayoutWin.h"
#include "ImProcWin.h"
#include "CameraWin.h"
#include "PokerGameWin.h"
#include "MainWin.h"
#include "LiveImageWin.h"
#include "CardImageWin.h"
#include "RankImageWin.h"
#include "SuitImageWin.h"
#include "LayoutConfig.h"

#include "BaseGUI.h"

namespace gui {

	class GUI: public BaseGUI
	{
		private:

            std::shared_ptr<shared::DataDetectGui> data_detect_;
            std::shared_ptr<shared::DataPokerGui> data_poker_;
       	std::shared_ptr<shared::CameraControls> camera_control_;
            std::shared_ptr<shared::DefaultConfig> default_config_;
            std::shared_ptr<LayoutConfig> layout_config_;

            LayoutWin layout_;
            ImProcWin img_proc_settings_;
            CameraWin camera_settings_;
            PokerGameWin poker_game_;
            MainWin main_win_;
            LiveImageWin live_view_;
            CardImageWin card_images_;
            RankImageWin rank_images_;
            SuitImageWin suit_images_;

            bool show_game_window_;
            bool show_frame_;
            bool show_main_window_;
            bool cam_control_changed_;
            bool show_layout_window_;
            const int card_image_height_ = 150;
            const int card_rank_suit_height_ = 50;
           
            void saveAsDefault();
            void setToDefault();

		public:

            bool camControlsChanged() { return this->cam_control_changed_; };
            void drawGui(const cv::Mat& live_frame);
      					
	        GUI(std::shared_ptr<shared::DataDetectGui>& data_detect, std::shared_ptr<shared::DataPokerGui>& data_poker, std::shared_ptr<shared::CameraControls>& camera_control, 
                  std::shared_ptr<shared::DefaultConfig> default_config):  
                    BaseGUI(), cam_control_changed_(false), data_detect_(data_detect), data_poker_(data_poker), camera_control_(camera_control), show_game_window_(true),
                    default_config_(default_config), layout_config_(std::make_shared<LayoutConfig>() ),
                    layout_{"Gui Layout", this->default_config_, this->layout_config_}, 
                    img_proc_settings_("Image Processing Settings", this->default_config_, this->data_detect_),  
                    camera_settings_("Camera Settings", this->default_config_, this->camera_control_),
                    poker_game_("Poker Game", this->default_config_, this->data_poker_, this->data_detect_->robot_cards, this->data_detect_->public_cards),
                    main_win_("Main Window"), 
                    live_view_("Live View", this->layout_config_->show_cards, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize),
                    card_images_("Card Images", ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize),
                    rank_images_("Binarized Ranks", ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize),
                    suit_images_("Binarized Suits", ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)
                    {
                        this->setToDefault(); 
                    };
	        ~GUI(){};

		    // Using default copy and move constructors. 
		    GUI(const GUI& other) = default;	
		    GUI& operator=(const GUI& other) = default;
		    GUI(GUI&& other) noexcept = default;
		    GUI& operator=(GUI&& other) noexcept = default;
	};

} // namespace gui

