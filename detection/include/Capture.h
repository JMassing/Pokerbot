#pragma once
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>


namespace detect {

	class Capture
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;

		public:
			cv::Mat frame_;

			bool init();
			bool grabLive();
			bool grabVideo();
	
			Capture();
			explicit Capture(const std::string& video);
			~Capture();

			// Using default copy and move constructors. 
			Capture(const Capture& other) = default;	
			Capture& operator=(const Capture& other) = default;
			Capture(Capture&& other) noexcept = default;
			Capture& operator=(Capture&& other) noexcept = default;
			
	};

}

