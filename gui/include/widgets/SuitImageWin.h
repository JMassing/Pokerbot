#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.h"
#include "Card.h"
#include "Window.h"

namespace gui {

	class SuitImageWin : public Window
	{
		private:

			ImageDrawer drawer_;
			int image_height_;
			std::vector<detect::Card> cards_;
			int image_height_percent_;

			virtual bool content() override;

		public:

			void update(const int& image_height, const std::vector<detect::Card>& cards, const int& card_image_height_percent);

		
			SuitImageWin(const std::string& name, const int& flag = 0): 
				Window(name, flag), image_height_(0), cards_{}, image_height_percent_{} {};
			virtual ~SuitImageWin() {};

			// Using default copy and move constructors. 
			SuitImageWin(const SuitImageWin& other) = default;	
			SuitImageWin& operator=(const SuitImageWin& other) = default;
			SuitImageWin(SuitImageWin&& other) noexcept = default;
			SuitImageWin& operator=(SuitImageWin&& other) noexcept = default;
	};

} // namespace gui

