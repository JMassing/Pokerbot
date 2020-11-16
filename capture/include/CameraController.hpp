#pragma once
/**
 * @file CameraController.hpp
 * @author Julian Massing (julimassing@gmail.com)
 * @brief Controls the video I/O using OpenCV VideoCapture class. 
 * 		  Using the setCameraControls method, camera settings can be changed (e.g. exposure time)
 *		  The grabLive method is used to grab live images from a camera
 *  	  The grabVideo method is used to grab frames from a video file
 * @version 1.0
 * @date 2020-11-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#include <string>
#include <memory>

#include <opencv2/videoio.hpp>

#include "ICameraDevice.hpp"
#include "ICaptureGui.hpp"
#include "Image.hpp"

namespace capture {

	class CameraController: public ICameraDevice
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;
			std::shared_ptr<ICaptureGui> gui_interface_;

		public:
			Image frame_;

			bool initCamera(const CameraSettings& camera_settings) override;
			/**
			 * @brief Grabs live Image from camera
			 * 
			 * @return true Image was grabbed
			 * @return false No Image was grabbed
			 */
			bool grabLive() override;
			bool grabVideo();
			void setCameraControls(const CameraSettings& camera_settings) override;
			void printCameraState();
			void attachGuiInterface(std::shared_ptr<ICaptureGui> interface)
			{
				this->gui_interface_ = interface;
			}
			int getBackend()
			{
				return this->cap_.get(cv::CAP_PROP_BACKEND);
			}
			
			// Constructor used to caputre live frame from camera
			CameraController(
				const int& device_ID = 0, 
				const int& api_ID = cv::CAP_ANY
				):
				device_ID_(device_ID), 
				frame_{}, 
				cap_{}, 
				api_ID_(api_ID),
				gui_interface_(nullptr)
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

