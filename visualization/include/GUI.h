#pragma once

#include <utility>

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
            const int image_width_ = 1248;
            const int image_height_ = 800;

            void drawImage(const cv::Mat& frame, const std::vector<detect::Card>& cards);
            void drawMainWindow(const std::pair<double,double>& probability);

		public:

            void GUI::drawGui(const cv::Mat& frame, const std::vector<detect::Card>& cards, const std::pair<double,double>& probability);
      					
			GUI():BaseGUI(), visualize_(), show_frame_(true), show_cards_(true) {};
			~GUI(){};

			// Using default copy and move constructors. 
			GUI(const GUI& other) = default;	
			GUI& operator=(const GUI& other) = default;
			GUI(GUI&& other) noexcept = default;
			GUI& operator=(GUI&& other) noexcept = default;
	};

   
} // namespace visualization

