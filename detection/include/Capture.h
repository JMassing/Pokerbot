#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "CameraControls.h"
#include "Image.h"
#include "IObserver.h"
#include "ControlsWin.h"

namespace detect {

	class Capture: public interfaces::IObserver
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;
			shared::CameraControls& camera_settings_;
			const gui::ControlsWin& controls_;

		public:
			Image frame_;

			void update() override;
			bool init();
			bool grabLive();
			bool grabVideo();
			void setCameraControls();
			void printCameraState();
			
			Capture(const gui::ControlsWin& controls, shared::CameraControls& camera_settings, const int& device_ID = 0, const int& api_ID = cv::CAP_ANY);
			Capture(const std::string& video, const gui::ControlsWin& controls, shared::CameraControls& camera_settings, const int& device_ID = 0, const int& api_ID = cv::CAP_ANY);
			~Capture();

			// Using default copy and move constructors. 
			Capture(const Capture& other) = default;	
			Capture& operator=(const Capture& other) = default;
			Capture(Capture&& other) noexcept = default;
			Capture& operator=(Capture&& other) noexcept = default;
			
	};

}

