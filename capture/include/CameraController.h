#pragma once

#include <string>
#include <memory>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "CameraSettings.h"
#include "Image.h"
#include "IObserver.h"
#include "GUICaptureOutput.h"

namespace capture {

	class CameraController
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;

		public:
			Image frame_;

			bool init(const CameraSettings& camera_settings);
			bool grabLive();
			bool grabVideo();
			void setCameraControls(const CameraSettings& camera_settings);
			void printCameraState();
			
			CameraController(
				const int& device_ID = 0, 
				const int& api_ID = cv::CAP_ANY
				):
				device_ID_(device_ID), 
				frame_{}, 
				cap_{}, 
				api_ID_(api_ID) 
			{};

			CameraController(
				const std::string& video,
				const int& device_ID = 0, 
				const int& api_ID = cv::CAP_ANY
				): 
				frame_{}, 
				cap_(video), 
				device_ID_(device_ID), 
				api_ID_(api_ID) 
			{};

			~CameraController() {};

			// Using default copy and move constructors. 
			CameraController(const CameraController& other) = default;	
			CameraController& operator=(const CameraController& other) = default;
			CameraController(CameraController&& other) noexcept = default;
			CameraController& operator=(CameraController&& other) noexcept = default;
			
	};

}

