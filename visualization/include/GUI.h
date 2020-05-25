#pragma once

#include <utility>
#include <vector>
#include <array>

#include <opencv2/core.hpp>

#include "View.h"
#include "Card.h"

#include "BaseGUI.h"

namespace visualization {

	class GUI: public BaseGUI
	{
		private:

            View visualize_;
            bool show_frame_;
            bool show_cards_;
            bool show_developer_window_;
            bool show_main_window_;
            bool show_card_images_;
            bool show_rank_images_;
            bool show_suit_images_;
            const int live_image_width_ = 1248;
            const int live_image_height_ = 800;

            float threshold;    

            void drawLiveView(const cv::Mat& frame, const std::vector<detect::Card>& cards);
            void drawMainWindow(const std::pair<double,double>& probability);
            void drawCardImages(const std::vector<detect::Card>& cards);
            void drawRankImages(const std::vector<detect::Card>& cards);
            void drawSuitImages(const std::vector<detect::Card>& cards);
            void drawImage(const cv::Mat& frame, const int& image_width, const int& image_height);
            void drawDeveloperWindow();

		public:

            void GUI::drawGui(const cv::Mat& frame, const std::array<detect::Card,2>& robot_cards, const std::vector<detect::Card>& public_cards, const std::pair<double,double>& probability);
      					
			GUI():BaseGUI(), visualize_(), show_frame_(true), show_cards_(true), show_developer_window_(false),
                show_main_window_(true), show_card_images_(false), show_rank_images_(false), show_suit_images_(false), threshold(0) {};
			~GUI(){};

			// Using default copy and move constructors. 
			GUI(const GUI& other) = default;	
			GUI& operator=(const GUI& other) = default;
			GUI(GUI&& other) noexcept = default;
			GUI& operator=(GUI&& other) noexcept = default;
	};

   
} // namespace visualization

