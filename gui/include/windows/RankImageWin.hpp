#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.hpp"
#include "GuiPokerInterface.hpp"

namespace gui {
	/**  \ingroup gui
	* @class RankImageWin
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Window showing binarized images of card ranks.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class RankImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
            LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;
			std::shared_ptr<GuiPokerInterface>& poker_if_;

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
				std::shared_ptr<GuiPokerInterface>& poker_if,
				const int& flag = 0
				): 
				IWindow(name, show, flag), 
				controls_(controls), 
				cards_{cards},
				poker_if_{poker_if}
			{};
				
			virtual ~RankImageWin() {};

			// Using default copy and move constructors. 
			RankImageWin(const RankImageWin& other) = default;	
			RankImageWin& operator=(const RankImageWin& other) = default;
			RankImageWin(RankImageWin&& other) noexcept = default;
			RankImageWin& operator=(RankImageWin&& other) noexcept = default;
	};

} // namespace gui

