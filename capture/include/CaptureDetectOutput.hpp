#pragma once

// CaptureOutput exposes captured live frame to modules that use it.

#include "IDetectCapture.hpp"
#include "Image.hpp"

namespace capture {

	class CaptureDetectOutput: public detect::IDetectCapture
	{ 

		private:
			Image& frame_;
			
		public:

			Image getImage() const override { return this->frame_; }
						
			explicit CaptureDetectOutput(Image& frame): frame_(frame) {};

			~CaptureDetectOutput() {};

			// Using default copy and move constructors. 
			CaptureDetectOutput(const CaptureDetectOutput& other) = default;	
			CaptureDetectOutput& operator=(const CaptureDetectOutput& other) = default;
			CaptureDetectOutput(CaptureDetectOutput&& other) noexcept = default;
			CaptureDetectOutput& operator=(CaptureDetectOutput&& other) noexcept = default;			
	};

} //end namespace capture

