#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.h"
#include "View.h"

namespace gui {

	class LiveImageWin : public IWindow
	{
		private:

			View visualize_;
			ImageDrawer drawer_;
			capture::Image& live_frame_;
			LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;

			bool show_;

		public:

			bool draw() override;

			LiveImageWin(
				const std::string& name, 
				LayoutConfig& controls, 
				capture::Image& live_frame, 
				std::vector<detect::Card>& cards,
				const int& flag = 0
				): 
				IWindow(name, flag), 
				show_(true), 
				live_frame_(live_frame), 
				controls_(controls), 
				cards_{cards},
				visualize_{}
			{};
				
			virtual ~LiveImageWin() {};

			// Using default copy and move constructors. 
			LiveImageWin(const LiveImageWin& other) = default;	
			LiveImageWin& operator=(const LiveImageWin& other) = default;
			LiveImageWin(LiveImageWin&& other) noexcept = default;
			LiveImageWin& operator=(LiveImageWin&& other) noexcept = default;
	};

} // namespace gui

