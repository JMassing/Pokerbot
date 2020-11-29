#include "CameraController.hpp"

namespace capture {

	bool CameraController::initCamera(const CameraSettings& camera_settings)
	{
		// set camera controls to default values during initialization
		this->cam_->open();

		// check if we succeeded
		if (!this->cam_->isOpened()) {
			return false;
		}

		// set initial camera settings
		this->setCameraControls(camera_settings);

		return true;
	}

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

		this->cam_->read();
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
	
	bool CameraController::grabVideo()
	{ 
		cam_->read();
		if (this->frame_.image.empty()) {
			return false;
		}
		return true;
	}

	void CameraController::setCameraControls(const CameraSettings& camera_settings)
	{
		this->cam_->set(cv::CAP_PROP_AUTOFOCUS, camera_settings.auto_focus);
		this->cam_->set(cv::CAP_PROP_AUTO_EXPOSURE, camera_settings.auto_exposure);
		this->cam_->set(cv::CAP_PROP_AUTO_WB, camera_settings.auto_wb);
		if(!camera_settings.auto_exposure)
		{
			this->cam_->set(cv::CAP_PROP_EXPOSURE, camera_settings.exposure_time);
		}
		if(!camera_settings.auto_focus)
		{
			this->cam_->set(cv::CAP_PROP_FOCUS, camera_settings.focus);
		}
		if(!camera_settings.auto_wb)
		{
			this->cam_->set(cv::CAP_PROP_WB_TEMPERATURE, camera_settings.wb_temperature);
		}
		this->cam_->set(cv::CAP_PROP_BRIGHTNESS, camera_settings.brightness);
		this->cam_->set(cv::CAP_PROP_ZOOM, camera_settings.zoom);
	}

	void CameraController::printCameraState()
	{
		std::cout << "Backend: " << this->cam_->get(cv::CAP_PROP_BACKEND) << "\n"
		<< "Backend Name: " << this->cam_->getBackendName() << "\n"
		<< "Autofocus: " << this->cam_->get(cv::CAP_PROP_AUTOFOCUS) << "\n"
		<< "AutoWB: " << this->cam_->get(cv::CAP_PROP_AUTO_WB) << "\n"
		<< "Auto Exposure: " << this->cam_->get(cv::CAP_PROP_AUTO_EXPOSURE) << "\n"
		<< "Exposure time: " << this->cam_->get(cv::CAP_PROP_EXPOSURE) << "\n"
		<< "Focus: " << this->cam_->get(cv::CAP_PROP_FOCUS) << "\n"
		<< "Brightness: " << this->cam_->get(cv::CAP_PROP_BRIGHTNESS) << "\n"
		<< "Zoom: " << this->cam_->get(cv::CAP_PROP_ZOOM) << std::endl << "\n"
		// << "Gamma: " << this->cam_->get(cv::CAP_PROP_GAMMA) << std::endl << "\n"
		<< "Saturation: " << this->cam_->get(cv::CAP_PROP_SATURATION) << std::endl << "\n"
		// << "Hue: " << this->cam_->get(cv::CAP_PROP_HUE) << std::endl << "\n"
		<< "Gain: " << this->cam_->get(cv::CAP_PROP_GAIN) << std::endl << "\n"
		<< "WB TEMP: " << this->cam_->get(cv::CAP_PROP_WB_TEMPERATURE) << std::endl << "\n"
		<< "WB BLUE: " << this->cam_->get(cv::CAP_PROP_WHITE_BALANCE_BLUE_U) << std::endl << "\n"
		<< "WB RED: " << this->cam_->get(cv::CAP_PROP_WHITE_BALANCE_RED_V) << std::endl << "\n";

	}

}