#pragma once

#include <utility>
#include <vector>
#include <memory>

#include <opencv2/core.hpp>
#include <functional>

#include "View.h"
#include "Card.h"
#include "CaptureTrainImg.h"
#include "Mapping.h"
#include "DataDetectGui.h"
#include "DataPokerGui.h"
#include "CameraControls.h"
#include "ImProc.h"
#include "DefaultConfig.h"
#include "LayoutWin.h"

#include "BaseGUI.h"

namespace gui {

	class GUI: public BaseGUI
	{
		private:

            View visualize_;
            detect::Mapping mapping_;
            std::shared_ptr<shared::DataDetectGui> data_detect_;
            std::shared_ptr<shared::DataPokerGui> data_poker_;
       	std::shared_ptr<shared::CameraControls> camera_control_;
            std::shared_ptr<shared::DefaultConfig> default_config_;

            CaptureTrainImg capture_train_img_;
            LayoutWin layout_;
            bool show_frame_;
            bool show_cards_;
            bool show_im_proc_settings_window_;
            bool show_main_window_;
            bool show_card_images_;
            bool show_rank_images_;
            bool show_suit_images_;
            bool show_camera_control_;
            bool cam_control_changed_;
            bool show_layout_window_;
            int live_image_width_;
            int live_image_height_; 
            bool show_ask_for_save_im_proc_;
            bool show_ask_for_save_layout_;
            bool show_ask_for_save_camera_;
            const int card_image_height_ = 150;
            const int card_rank_suit_height_ = 50;
            int card_image_height_percent_;
            int card_rank_suit_height_percent_;
            cv::Scalar card_outline_color_;  

            template<class T>
            void enforceBoundaries(const T& min, const T& max, T& value);
            void drawLiveView(const cv::Mat& frame, const std::vector<detect::Card>& cards);
            void drawMainWindow();
            void askForSave(bool& save, bool& show, std::string type);
            void drawCardImages(const std::vector<detect::Card>& cards);
            void drawRankImages(const std::vector<detect::Card>& cards);
            void drawSuitImages(const std::vector<detect::Card>& cards);
            void drawImage(const cv::Mat& frame, const int& image_width, const int& image_height);
            void drawImageProcSettingsWindow();
            void drawCameraControl();
            void saveAsDefault();
            void setToDefault();

		public:

            bool camControlsChanged(){return this->cam_control_changed_;};
            void drawGui(const cv::Mat& frame);
      					
	        GUI(std::shared_ptr<shared::DataDetectGui>& data_detect, std::shared_ptr<shared::DataPokerGui>& data_poker, std::shared_ptr<shared::CameraControls>& camera_control, std::shared_ptr<shared::DefaultConfig> default_config):  
                    BaseGUI(), visualize_(), cam_control_changed_(false), capture_train_img_(), mapping_(),  data_detect_(data_detect), data_poker_(data_poker), camera_control_(camera_control), 
                    default_config_(default_config), show_ask_for_save_im_proc_(false), show_ask_for_save_layout_(false), show_ask_for_save_camera_(false), layout_{"Gui Layout", this->default_config_}
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

      template<class T>
      void GUI::enforceBoundaries(const T& min, const T& max, T& value)
      {
            if(value < min)
            {
                  value = min;
            }
            else if(value > max)
            {
                  value = max;
            }
            else
            {
                  //do nothing
            }
            
      }

} // namespace gui

