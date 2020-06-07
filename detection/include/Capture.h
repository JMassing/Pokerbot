#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "CameraControls.h"
#include "Parameters.h"
#include "Image.h"

namespace detect {

	class Capture
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;
			std::shared_ptr<CameraControls> camera_control_;

		public:
			Image frame_;

			bool init();
			bool grabLive();
			bool grabVideo();
			void setCameraControls();
			void printCameraState();
			
			Capture(std::shared_ptr<CameraControls>& camera_control, parameters::Config& default);
			Capture(const std::string& video, std::shared_ptr<CameraControls>& camera_control, parameters::Config& default);
			~Capture();

			// Using default copy and move constructors. 
			Capture(const Capture& other) = default;	
			Capture& operator=(const Capture& other) = default;
			Capture(Capture&& other) noexcept = default;
			Capture& operator=(Capture&& other) noexcept = default;
			
	};

}

