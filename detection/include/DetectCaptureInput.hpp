#pragma once

// Observes CaptureOutput and gets live frame

#include <memory>

#include "CaptureOutput.hpp"
#include "IObserver.hpp"
#include "ICardDetector.hpp"

namespace detect {

	class DetectCaptureInput: public interfaces::IObserver
	{ 
		private:
			
			capture::CaptureOutput& cap_out_;
			std::shared_ptr<ICardDetector> detector_;

		public:
			
			void update() override
            {                
				this->detector_->updateFrame(this->cap_out_.getLiveFrame());
            };

			void connectCardDetector(std::shared_ptr<ICardDetector> detector)
			{
				this->detector_ = detector;
			}
			
			DetectCaptureInput(capture::CaptureOutput& cap_out):
				cap_out_(cap_out),
				detector_{}
			{};

			~DetectCaptureInput() {};

			// Using default copy and move constructors. 
			DetectCaptureInput(const DetectCaptureInput& other) = default;	
			DetectCaptureInput& operator=(const DetectCaptureInput& other) = default;
			DetectCaptureInput(DetectCaptureInput&& other) noexcept = default;
			DetectCaptureInput& operator=(DetectCaptureInput&& other) noexcept = default;			
	};

} //end namespace detect