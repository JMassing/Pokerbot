#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "CameraControls.h"

namespace detect {

	class Capture
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;
			std::shared_ptr<CameraControls> camera_control_;

		public:
			cv::Mat frame_;

			bool init();
			bool grabLive();
			bool grabVideo();
			void setCameraControls();
			void printCameraState();
			
			explicit Capture(std::shared_ptr<CameraControls>& camera_control);
			Capture(const std::string& video, std::shared_ptr<CameraControls>& camera_control);
			~Capture();

			// Using default copy and move constructors. 
			Capture(const Capture& other) = default;	
			Capture& operator=(const Capture& other) = default;
			Capture(Capture&& other) noexcept = default;
			Capture& operator=(Capture&& other) noexcept = default;
			
	};

}

