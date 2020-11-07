#include "CameraController.hpp"

namespace capture {

	// @brief: open selected camera using selected API
	bool CameraController::initCamera(const CameraSettings& camera_settings)
	{
		// set camera controls to default values during initialization
		this->cap_.open(this->device_ID_ + this->api_ID_);

		// check if we succeeded
		if (!this->cap_.isOpened()) {
			return false;
		}

		// set initial camera settings
		this->setCameraControls(camera_settings);

		return true;
	}

	//@brief: Grab live image from camera
	bool CameraController::grabLive()
	{
		// Set Camera settings if they were changed if gui is connected
		if(this->gui_interface_ != nullptr)
		{
			if(this->gui_interface_->checkUserInput())
			{
				this->setCameraControls(this->gui_interface_->getSettings());
			}
		}

		this->cap_.read(this->frame_.image);
		if (this->frame_.image.empty()) {
			return false;
		}

		// Send live image to gui for display if gui is connected
		if(this->gui_interface_ != nullptr)
		{
			this->gui_interface_->setImage(this->frame_);
		}
		

		return true;
	}
	
	//@brief: Grab image from Video
	bool CameraController::grabVideo()
	{ 
		cap_ >> this->frame_.image;
		if (this->frame_.image.empty()) {
			return false;
		}
		return true;
	}

	//@brief: Sets Controls of camera (e.g. exposure, brightness, ...). Input from 
	//		  camera_control_ shared object with GUI
	void CameraController::setCameraControls(const CameraSettings& camera_settings)
	{
		this->cap_.set(cv::CAP_PROP_AUTOFOCUS, camera_settings.auto_focus);
		this->cap_.set(cv::CAP_PROP_AUTO_EXPOSURE, camera_settings.auto_exposure);
		this->cap_.set(cv::CAP_PROP_AUTO_WB, camera_settings.auto_wb);
		if(!camera_settings.auto_exposure)
		{
			this->cap_.set(cv::CAP_PROP_EXPOSURE, camera_settings.exposure_time);
		}
		if(!camera_settings.auto_focus)
		{
			this->cap_.set(cv::CAP_PROP_FOCUS, camera_settings.focus);
		}
		if(!camera_settings.auto_wb)
		{
			this->cap_.set(cv::CAP_PROP_WB_TEMPERATURE, camera_settings.wb_temperature);
		}
		this->cap_.set(cv::CAP_PROP_BRIGHTNESS, camera_settings.brightness);
		this->cap_.set(cv::CAP_PROP_ZOOM, camera_settings.zoom);
	}

	void CameraController::printCameraState()
	{
		std::cout << "Backend: " << this->cap_.get(cv::CAP_PROP_BACKEND) << "\n"
		<< "Backend Name: " << this->cap_.getBackendName() << "\n"
		<< "Autofocus: " << this->cap_.get(cv::CAP_PROP_AUTOFOCUS) << "\n"
		<< "AutoWB: " << this->cap_.get(cv::CAP_PROP_AUTO_WB) << "\n"
		<< "Auto Exposure: " << this->cap_.get(cv::CAP_PROP_AUTO_EXPOSURE) << "\n"
		<< "Exposure time: " << this->cap_.get(cv::CAP_PROP_EXPOSURE) << "\n"
		<< "Focus: " << this->cap_.get(cv::CAP_PROP_FOCUS) << "\n"
		<< "Brightness: " << this->cap_.get(cv::CAP_PROP_BRIGHTNESS) << "\n"
		<< "Zoom: " << this->cap_.get(cv::CAP_PROP_ZOOM) << std::endl << "\n"
		// << "Gamma: " << this->cap_.get(cv::CAP_PROP_GAMMA) << std::endl << "\n"
		<< "Saturation: " << this->cap_.get(cv::CAP_PROP_SATURATION) << std::endl << "\n"
		// << "Hue: " << this->cap_.get(cv::CAP_PROP_HUE) << std::endl << "\n"
		<< "Gain: " << this->cap_.get(cv::CAP_PROP_GAIN) << std::endl << "\n"
		<< "WB TEMP: " << this->cap_.get(cv::CAP_PROP_WB_TEMPERATURE) << std::endl << "\n"
		<< "WB BLUE: " << this->cap_.get(cv::CAP_PROP_WHITE_BALANCE_BLUE_U) << std::endl << "\n"
		<< "WB RED: " << this->cap_.get(cv::CAP_PROP_WHITE_BALANCE_RED_V) << std::endl << "\n";

	}

}