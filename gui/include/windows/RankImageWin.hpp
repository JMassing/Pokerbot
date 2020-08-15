#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.hpp"

namespace gui {

	class RankImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
            LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;

            // initial sizes of displayed card images
            const double aspect_ratio_ = 1;
			const int image_height_ = 50;

		public:

			void draw() override;

			RankImageWin(
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
				
			virtual ~RankImageWin() {};

			// Using default copy and move constructors. 
			RankImageWin(const RankImageWin& other) = default;	
			RankImageWin& operator=(const RankImageWin& other) = default;
			RankImageWin(RankImageWin&& other) noexcept = default;
			RankImageWin& operator=(RankImageWin&& other) noexcept = default;
	};

} // namespace gui
