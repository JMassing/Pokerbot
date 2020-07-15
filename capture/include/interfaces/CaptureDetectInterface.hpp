#pragma once

// CaptureDetectInterface exposes captured live frame to detection module.

#include "IDetectCapture.hpp"
#include "Image.hpp"

namespace capture {

	class CaptureDetectInterface: public detect::IDetectCapture
	{ 

		private:
			Image& frame_;
			
		public:

			Image getImage() const override { return this->frame_; }
						
			explicit CaptureDetectInterface(Image& frame): frame_(frame) {};

			~CaptureDetectInterface() {};

			// Using default copy and move constructors. 
			CaptureDetectInterface(const CaptureDetectInterface& other) = default;	
			CaptureDetectInterface& operator=(const CaptureDetectInterface& other) = default;
			CaptureDetectInterface(CaptureDetectInterface&& other) noexcept = default;
			CaptureDetectInterface& operator=(CaptureDetectInterface&& other) noexcept = default;			
	};

} //end namespace capture

