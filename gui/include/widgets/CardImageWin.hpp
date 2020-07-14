#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.hpp"

namespace gui {

	class CardImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
            LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;

            // initial sizes of displayed card images
            const double aspect_ratio_ = 1.4;
			const int image_height_ = 150;

		public:

			void draw() override;

			CardImageWin(
				const std::string& name, 
				bool& show,
				LayoutConfig& controls, 
				std::vector<detect::Card>& cards,
				const int& flag = 0
				): 
				IWindow(name, show, flag), 
				controls_(controls), 
				cards_{cards}
			{};
				
			virtual ~CardImageWin() {};

			// Using default copy and move constructors. 
			CardImageWin(const CardImageWin& other) = default;	
			CardImageWin& operator=(const CardImageWin& other) = default;
			CardImageWin(CardImageWin&& other) noexcept = default;
			CardImageWin& operator=(CardImageWin&& other) noexcept = default;
	};

} // namespace gui

