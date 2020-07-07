#pragma once

// Observes CaptureOutput and gets live frame

#include <memory>

#include "CaptureOutput.hpp"
#include "IObserver.hpp"
#include "Image.hpp"

namespace detect {

	class DetectCaptureInput: public interfaces::IObserver
	{ 
		public:

			capture::Image frame_;
			capture::CaptureOutput& cap_out_;
			
			void update() override
            {
                this->frame_ = this->cap_out_.getLiveFrame();
            };
			
			DetectCaptureInput(capture::CaptureOutput& cap_out):
				cap_out_(cap_out),
				frame_{}
			{};

			~DetectCaptureInput() {};

			// Using default copy and move constructors. 
			DetectCaptureInput(const DetectCaptureInput& other) = default;	
			DetectCaptureInput& operator=(const DetectCaptureInput& other) = default;
			DetectCaptureInput(DetectCaptureInput&& other) noexcept = default;
			DetectCaptureInput& operator=(DetectCaptureInput&& other) noexcept = default;			
	};

} //end namespace detect