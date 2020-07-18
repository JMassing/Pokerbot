#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.hpp"
#include "IWindow.hpp"
#include "Image.hpp"
#include "LayoutConfig.hpp"
#include "Card.hpp"

namespace gui {

	class LiveImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
			Image& live_frame_;
			LayoutConfig& controls_;
			std::vector<detect::Card>& cards_;
			int& game_state_;
			
			void print_instructions(cv::Mat& live_image);

		public:

			void draw() override;

			LiveImageWin(
				const std::string& name, 
				bool& show,
				LayoutConfig& controls, 
				Image& live_frame, 
				std::vector<detect::Card>& cards,
				int& game_state,
				const int& flag = 0
				): 
				IWindow(name, show, flag), 
				live_frame_(live_frame), 
				controls_(controls), 
				cards_{cards},
				game_state_{game_state}
			{};
				
			virtual ~LiveImageWin() {};

			// Using default copy and move constructors. 
			LiveImageWin(const LiveImageWin& other) = default;	
			LiveImageWin& operator=(const LiveImageWin& other) = default;
			LiveImageWin(LiveImageWin&& other) noexcept = default;
			LiveImageWin& operator=(LiveImageWin&& other) noexcept = default;
	};

} // namespace gui

