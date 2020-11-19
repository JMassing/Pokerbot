#pragma once



#include <string>
#include <memory>

#include <opencv2/videoio.hpp>

#include "ICameraDevice.hpp"
#include "ICaptureGui.hpp"
#include "Image.hpp"

namespace capture {
	/**
	* @class CameraController
	* @author Julian Massing (julimassing@gmail.com)
	* @brief This class controls the video I/O. It implements the CameraDevice interface using the OpenCV VideoCapture class.
	*		
	* @version 1.0
	* @date 2020-11-16
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	
	class CameraController: public ICameraDevice
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;
			std::shared_ptr<ICaptureGui> gui_interface_;

		public:
			Image frame_;

			/**
			 * @brief Initializes camera and sets camera controls to initial settings
			 * 
			 * @param camera_settings Initial camera settings (e.g. exposure time)
			 * @return true if camera was initialized
			 * @return false if camera could not be initialized
			 */
			bool initCamera(const CameraSettings& camera_settings) override;
			/**
			 * @brief Stores image from live camera feed in class member frame_. If camera settings (e.g. exposure time)
			 * are changed via user input in GUI, camera controls are set to new values before image grabbing
			 * 
			 * @return true if frame was stored
			 * @return false if frame could not be stored
			 */
			bool grabLive() override;
			/**
			 * @brief Stores image from video file in class member frame_
			 * 
			 * @return true if frame was stored
			 * @return false if frame could not be stored
			 */
			bool grabVideo();
			/**
			 * @brief Set camera controls according to camera settings (e.g. exposure time)
			 * 
			 * @param camera_settings 
			 */
			void setCameraControls(const CameraSettings& camera_settings) override;
			/**
			 * @brief Print the currently set camera controls to console
			 * 
			 */
			void printCameraState();
			/**
			 * @brief Attach communication interface between Capture and GUI modules. 
			 * 
			 * @param interface Pointer to the Capture/GUI interface. 
			 */
			void attachGuiInterface(std::shared_ptr<ICaptureGui> interface)
			{
				this->gui_interface_ = interface;
			}
			/**
			 * @brief Returns the currently used camera backend
			 * 
			 * @return int rerpresenting OpenCV ID of camera backend (see OpenCV manual)
			 */
			int getBackend()
			{
				return this->cap_.get(cv::CAP_PROP_BACKEND);
			}
			
			/**
			 * @brief Default Constructor 
			 * 
			 * @param device_ID Device ID of connected camera. 
			 * @param api_ID ID of camera backend API. See OpenCV Documentation for available APIs. Default will detect API automatically
			 * on camera init.  
			 */
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

			/**
			 * @brief Constructor overload for reading images from video file 
			 * 
			 * @param video Path to video file 
			 */
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

