#include "pch.h"
#include "Capture.h"

namespace detect {

	Capture::Capture() :frame_{}, cap_{}, device_ID_(1), api_ID_(cv::CAP_ANY)
	{
	}

	Capture::Capture(std::string video) : frame_{}, cap_(video), device_ID_(1), api_ID_(cv::CAP_ANY)
	{
	}

	Capture::~Capture()
	{
	}

	// open selected camera using selected API
	bool Capture::init()
	{
		this->cap_.open(this->device_ID_ + this->api_ID_);
		// check if we succeeded
		if (!this->cap_.isOpened()) {
			return false;
		}
		return true;
	}

	bool Capture::grabLive()
	{
		this->cap_.read(this->frame_);
		if (this->frame_.empty()) {
			return false;
		}
		return true;
	}

	bool Capture::grabVideo()
	{ 
		cap_ >> this->frame_;
		if (this->frame_.empty()) {
			return false;
		}
		return true;
	}
}