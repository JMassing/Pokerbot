#pragma once

#include <opencv2/core.hpp>
#include <vector>

#include "ImageDrawer.h"
#include "Card.h"
#include "View.h"
#include "IWindow.h"
#include "Image.h"
#include "IObserver.h"
#include "ControlsWin.h"

namespace gui {

	class LiveImageWin : public IWindow, public interfaces::IObserver
	{
		private:

			ImageDrawer drawer_;
			detect::Image& live_frame_;
			ControlsWin& controls_;

			int image_width_;
			int image_height_;
			bool show_;

		public:

			void update() override;
			bool draw() override;

			LiveImageWin(const std::string& name, ControlsWin& controls, detect::Image& live_frame, const int& flag = 0): 
				IWindow(name, flag), show_(true), live_frame_(live_frame), image_width_(1028), image_height_(780), controls_(controls) {};
			virtual ~LiveImageWin() {};

			// Using default copy and move constructors. 
			LiveImageWin(const LiveImageWin& other) = default;	
			LiveImageWin& operator=(const LiveImageWin& other) = default;
			LiveImageWin(LiveImageWin&& other) noexcept = default;
			LiveImageWin& operator=(LiveImageWin&& other) noexcept = default;
	};

} // namespace gui

