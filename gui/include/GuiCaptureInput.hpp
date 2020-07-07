#pragma once

#include <memory>
#include <iostream>

#include "IObserver.hpp"
#include "CaptureOutput.hpp"
#include "Image.hpp"

namespace gui {

	class GuiCaptureInput: public interfaces::IObserver
	{ 
		public:

			capture::Image frame_;
			capture::CaptureOutput& cap_out_;
			
			void update() override
            {
                this->frame_ = this->cap_out_.getLiveFrame();
            };
			
			GuiCaptureInput(capture::CaptureOutput& cap_out):
				cap_out_(cap_out),
				frame_{}
			{};

			~GuiCaptureInput() {};

			// Using default copy and move constructors. 
			GuiCaptureInput(const GuiCaptureInput& other) = default;	
			GuiCaptureInput& operator=(const GuiCaptureInput& other) = default;
			GuiCaptureInput(GuiCaptureInput&& other) noexcept = default;
			GuiCaptureInput& operator=(GuiCaptureInput&& other) noexcept = default;			
	};

}

