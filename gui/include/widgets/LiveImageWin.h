#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.h"
#include "Card.h"
#include "View.h"
#include "Window.h"

namespace gui {

	class LiveImageWin : public Window
	{
		private:

			ImageDrawer drawer_;
			View visualize_;
			bool& show_cards_;
			cv::Mat live_frame_;
			int image_width_;
			int image_height_;
			std::vector<detect::Card> cards_;
			cv::Scalar card_outline_color_;

			virtual bool content() override;

		public:

			void update(const cv::Mat& live_frame, const int& image_width, const int& image_height, const std::vector<detect::Card>& cards, const cv::Scalar& card_outline_color);

		
			LiveImageWin(const std::string& name, bool& show_cards, const int& flag = 0): 
				Window(name, flag), show_cards_(show_cards),  visualize_{},
				live_frame_{}, image_width_(0), image_height_(0), cards_{}, card_outline_color_{} {};
			virtual ~LiveImageWin() {};

			// Using default copy and move constructors. 
			LiveImageWin(const LiveImageWin& other) = default;	
			LiveImageWin& operator=(const LiveImageWin& other) = default;
			LiveImageWin(LiveImageWin&& other) noexcept = default;
			LiveImageWin& operator=(LiveImageWin&& other) noexcept = default;
	};

} // namespace gui

