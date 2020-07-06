#pragma once

#include <memory>

#include "ISubject.h"
#include "CameraSettings.h"
#include "SettingsWin.h"

namespace gui {

	class GUICaptureOutput: public interfaces::ISubject
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

        	explicit GUICaptureOutput(
				capture::CameraSettings camera_settings
				): 
				camera_settings_(camera_settings) 
			{};

			virtual ~GUICaptureOutput() {};

			// Using default copy and move constructors. 
			GUICaptureOutput(const GUICaptureOutput& other) = default;	
			GUICaptureOutput& operator=(const GUICaptureOutput& other) = default;
			GUICaptureOutput(GUICaptureOutput&& other) noexcept = default;
			GUICaptureOutput& operator=(GUICaptureOutput&& other) noexcept = default;
	};

} // namespace gui

 