#pragma once
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>


namespace detect {

	class Capture
	{ 
	public:
		cv::Mat frame_;
	private:
		cv::VideoCapture cap_;
		int device_ID_;
		int api_ID_;
	public:
		Capture();
		explicit Capture(std::string video);
		~Capture();

		bool init();
		bool grabLive();
		bool grabVideo();
	};

}

