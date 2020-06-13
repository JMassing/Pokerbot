#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.h"
#include "Card.h"
#include "Window.h"

namespace gui {

	class CardImageWin : public Window
	{
		private:

			ImageDrawer drawer_;
			int aspect_ratio_;
			int image_height_;
			std::vector<detect::Card> cards_;
			int image_height_percent_;

			virtual bool content() override;

		public:

			void update(const int& aspect_ratio, const int& image_height, const std::vector<detect::Card>& cards, const int& card_image_height_percent);

		
			CardImageWin(const std::string& name, const int& flag = 0): 
				Window(name, flag), aspect_ratio_(0), image_height_(0), cards_{}, image_height_percent_{} {};
			virtual ~CardImageWin() {};

			// Using default copy and move constructors. 
			CardImageWin(const CardImageWin& other) = default;	
			CardImageWin& operator=(const CardImageWin& other) = default;
			CardImageWin(CardImageWin&& other) noexcept = default;
			CardImageWin& operator=(CardImageWin&& other) noexcept = default;
	};

} // namespace gui

