#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.h"
#include "Card.h"
#include "View.h"
#include "IWindow.h"
#include "Image.h"
#include "IObserver.h"
#include "SettingsWin.h"

namespace gui {

	class LiveImageWin : public IWindow
	{
		private:

			ImageDrawer drawer_;
			capture::Image& live_frame_;
			SettingsWin& controls_;

			bool show_;

		public:

			bool draw() override;

			LiveImageWin(
				const std::string& name, 
				SettingsWin& controls, 
				capture::Image& live_frame, 
				const int& flag = 0
				): 
				IWindow(name, flag), 
				show_(true), 
				live_frame_(live_frame), 
				controls_(controls) 
				{};
				
			virtual ~LiveImageWin() {};

			// Using default copy and move constructors. 
			LiveImageWin(const LiveImageWin& other) = default;	
			LiveImageWin& operator=(const LiveImageWin& other) = default;
			LiveImageWin(LiveImageWin&& other) noexcept = default;
			LiveImageWin& operator=(LiveImageWin&& other) noexcept = default;
	};

} // namespace gui

