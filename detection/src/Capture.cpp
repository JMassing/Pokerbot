#include "Capture.h"

namespace detect {

	Capture::Capture(const gui::ControlsWin& controls, shared::CameraControls& camera_settings, const int& device_ID, const int& api_ID) :
		device_ID_(device_ID), frame_{}, cap_{}, api_ID_(api_ID), camera_settings_{camera_settings}, controls_(controls)
	{
	}

	Capture::Capture(const std::string& video, const gui::ControlsWin& controls, shared::CameraControls& camera_settings, const int& device_ID, const int& api_ID): 
		frame_{}, cap_(video), device_ID_(device_ID), api_ID_(api_ID), camera_settings_{camera_settings}, controls_(controls)
	{
	}

	Capture::~Capture()
	{
	}

	// @brief: open selected camera using selected API
	bool Capture::init()
	{
		// set camera controls to default values during initialization
		this->setCameraControls();
		this->cap_.open(this->device_ID_ + this->api_ID_);

		// check if we succeeded
		if (!this->cap_.isOpened()) {
			return false;
		}

		return true;
	}

	//@brief: Grab live image from camera
	bool Capture::grabLive()
	{
		this->cap_.read(this->frame_.image);
		if (this->frame_.image.empty()) {
			return false;
		}

		return true;
	}
	//@brief: Grab image from Video
	bool Capture::grabVideo()
	{ 
		cap_ >> this->frame_.image;
		if (this->frame_.image.empty()) {
			return false;
		}
		return true;
	}

	//@brief: Sets Controls of camera (e.g. exposure, brightness, ...). Input from camera_control_ shared object with GUI
	void Capture::setCameraControls()
	{
		this->cap_.set(cv::CAP_PROP_AUTOFOCUS, this->camera_settings_.auto_focus);
		this->cap_.set(cv::CAP_PROP_AUTO_EXPOSURE, this->camera_settings_.auto_exposure);
		this->cap_.set(cv::CAP_PROP_AUTO_WB, this->camera_settings_.auto_exposure);
		if(!this->camera_settings_.auto_exposure)
		{
			this->cap_.set(cv::CAP_PROP_EXPOSURE, this->camera_settings_.exposure_time);
		}
		if(!this->camera_settings_.auto_focus)
		{
			this->cap_.set(cv::CAP_PROP_FOCUS, this->camera_settings_.focus);
		}
		this->cap_.set(cv::CAP_PROP_BRIGHTNESS, this->camera_settings_.brightness);
		this->cap_.set(cv::CAP_PROP_ZOOM, this->camera_settings_.zoom);
	}

	void Capture::printCameraState()
	{
		std::cout << "Backend: " << this->cap_.get(cv::CAP_PROP_BACKEND) << "\n"
		<< "Backend Name: " << this->cap_.getBackendName() << "\n"
		<< "Autofocus: " << this->cap_.get(cv::CAP_PROP_AUTOFOCUS) << "\n"
		<< "AutoWB: " << this->cap_.get(cv::CAP_PROP_AUTO_WB) << "\n"
		<< "Auto Exposure: " << this->cap_.get(cv::CAP_PROP_AUTO_EXPOSURE) << "\n"
		<< "Exposure time: " << this->cap_.get(cv::CAP_PROP_EXPOSURE) << "\n"
		<< "Focus: " << this->cap_.get(cv::CAP_PROP_FOCUS) << "\n"
		<< "Brightness: " << this->cap_.get(cv::CAP_PROP_BRIGHTNESS) << "\n"
		<< "Zoom: " << this->cap_.get(cv::CAP_PROP_ZOOM) << std::endl;

	}

	void Capture::update()
	{
		this->camera_settings_ = controls_.camera_settings_;
		this->setCameraControls();		
	}
}