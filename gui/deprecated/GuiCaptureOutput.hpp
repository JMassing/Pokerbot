#pragma once

#include <memory>

#include "ISubject.hpp"
#include "CameraSettings.hpp"

namespace gui {

	class GuiCaptureOutput: public interfaces::ISubject
	{
		private:

		//Camera Controls
		capture::CameraSettings camera_settings_;

		public:			

            capture::CameraSettings getSettings() const 
			{
				 return this->camera_settings_;
			} 
			
			void checkForUserInput(
				const bool& input_flag, 
				const capture::CameraSettings& camera_settings
				) 
			{
				if(input_flag)
				{  
					this->camera_settings_ = camera_settings; 
					this->notify(); 
				};
			}

        	explicit GuiCaptureOutput(
				capture::CameraSettings camera_settings
				): 
				camera_settings_(camera_settings) 
			{};

			virtual ~GuiCaptureOutput() {};

			// Using default copy and move constructors. 
			GuiCaptureOutput(const GuiCaptureOutput& other) = default;	
			GuiCaptureOutput& operator=(const GuiCaptureOutput& other) = default;
			GuiCaptureOutput(GuiCaptureOutput&& other) noexcept = default;
			GuiCaptureOutput& operator=(GuiCaptureOutput&& other) noexcept = default;
	};

} // namespace gui

 