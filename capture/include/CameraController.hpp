#pragma once

// This class controls the video I/O. It controls the camera settings (e.g. exposure time)
// and captures live frames from the camera or frames from a video

#include <string>
#include <memory>

#include <opencv2/videoio.hpp>

#include "ICameraDevice.hpp"
#include "Image.hpp"

namespace capture {

	class CameraController: public ICameraDevice
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;

		public:
			Image frame_;

			bool initCamera(const CameraSettings& camera_settings) override;
			bool grabLive() override;
			bool grabVideo();
			void setCameraControls(const CameraSettings& camera_settings) override;
			void printCameraState();
			
			// Constructor used to caputre live frame from camera
			CameraController(
				const int& device_ID = 0, 
				const int& api_ID = cv::CAP_ANY
				):
				device_ID_(device_ID), 
				frame_{}, 
				cap_{}, 
				api_ID_(api_ID) 
			{};

			// Constructor used to capture from video file
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

} //end namespace capture

