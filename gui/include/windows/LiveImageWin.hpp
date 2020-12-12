#pragma once

#include <opencv2/core.hpp>
#include <vector>
#include <memory>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.hpp"
#include "GuiPokerInterface.hpp"

namespace gui {

	/**  \ingroup gui
	 * @class LiveImageWin
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Window that shows the live image
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class LiveImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
			Image& live_frame_;
			LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;
			std::shared_ptr<GuiPokerInterface>& poker_if_;
			
			void print_instructions(cv::Mat& live_image);

		public:

			void draw() override;

			LiveImageWin(
				const std::string& name, 
				bool& show,
				LayoutConfig& controls, 
				Image& live_frame, 
				std::vector<detect::Card>& cards,
				std::shared_ptr<GuiPokerInterface>& poker_if,
				const int& flag = 0
				): 
				IWindow(name, show, flag), 
				live_frame_(live_frame), 
				controls_(controls), 
				cards_{cards},
				poker_if_{poker_if},
				drawer_{}
			{ };
				
			virtual ~LiveImageWin() {};

			// Using default copy and move constructors. 
			LiveImageWin(const LiveImageWin& other) = default;	
			LiveImageWin& operator=(const LiveImageWin& other) = default;
			LiveImageWin(LiveImageWin&& other) noexcept = default;
			LiveImageWin& operator=(LiveImageWin&& other) noexcept = default;
	};

} // namespace gui

