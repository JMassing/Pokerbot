#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.h"
#include "Card.h"
#include "Window.h"

namespace gui {

	class RankImageWin : public Window
	{
		private:

			ImageDrawer drawer_;
			int image_height_;
			std::vector<detect::Card> cards_;
			int image_height_percent_;

			virtual bool content() override;

		public:

			void update(const int& image_height, const std::vector<detect::Card>& cards, const int& card_image_height_percent);

		
			RankImageWin(const std::string& name, const int& flag = 0): 
				Window(name, flag), image_height_(0), cards_{}, image_height_percent_{} {};
			virtual ~RankImageWin() {};

			// Using default copy and move constructors. 
			RankImageWin(const RankImageWin& other) = default;	
			RankImageWin& operator=(const RankImageWin& other) = default;
			RankImageWin(RankImageWin&& other) noexcept = default;
			RankImageWin& operator=(RankImageWin&& other) noexcept = default;
	};

} // namespace gui

