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
	 * @class SuitImageWin
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Window showing binarized images of card suits.
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class SuitImageWin : public IWindow
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

			SuitImageWin(
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
				
			virtual ~SuitImageWin() {};

			// Using default copy and move constructors. 
			SuitImageWin(const SuitImageWin& other) = default;	
			SuitImageWin& operator=(const SuitImageWin& other) = default;
			SuitImageWin(SuitImageWin&& other) noexcept = default;
			SuitImageWin& operator=(SuitImageWin&& other) noexcept = default;
	};

} // namespace gui

