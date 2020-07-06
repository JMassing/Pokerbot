#pragma once

// CaptureOutput exposes captured live frame to modules that use it.

#include <memory>

#include "ISubject.h"
#include "Image.h"

namespace capture {

	class CaptureOutput: public interfaces::ISubject
	{ 
		private:

		Image& frame_;
		
		public:

			Image getLiveFrame(){return this->frame_;}
						
			explicit CaptureOutput(Image& frame): frame_(frame) {};

			~CaptureOutput() {};

			// Using default copy and move constructors. 
			CaptureOutput(const CaptureOutput& other) = default;	
			CaptureOutput& operator=(const CaptureOutput& other) = default;
			CaptureOutput(CaptureOutput&& other) noexcept = default;
			CaptureOutput& operator=(CaptureOutput&& other) noexcept = default;			
	};

} //end namespace capture

