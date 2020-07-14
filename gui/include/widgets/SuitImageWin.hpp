#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.hpp"

namespace gui {

	class SuitImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
            LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;

            // initial sizes of displayed card images
            const double aspect_ratio_ = 1;
			const int image_height_ = 50;

		public:

			bool draw() override;

			SuitImageWin(
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
				
			virtual ~SuitImageWin() {};

			// Using default copy and move constructors. 
			SuitImageWin(const SuitImageWin& other) = default;	
			SuitImageWin& operator=(const SuitImageWin& other) = default;
			SuitImageWin(SuitImageWin&& other) noexcept = default;
			SuitImageWin& operator=(SuitImageWin&& other) noexcept = default;
	};

} // namespace gui

