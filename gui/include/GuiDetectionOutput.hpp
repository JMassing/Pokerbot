#pragma once

#include <memory>

#include "ISubject.hpp"
#include "ImProcSettings.hpp"

namespace gui {

	class GuiDetectionOutput: public interfaces::ISubject
	{
		private:

		//Camera Controls
		detect::ImProcSettings proc_settings_;

		public:			

            detect::ImProcSettings getSettings() const 
			{
				 return this->proc_settings_;
			} 
			
			void checkForUserInput(
				const bool& input_flag, 
				const detect::ImProcSettings proc_settings
				) 
			{
				if(input_flag)
				{  
					this->proc_settings_ = proc_settings_; 
					this->notify(); 
				};
			}

        	explicit GuiDetectionOutput(
				detect::ImProcSettings initial_settings
				): 
				proc_settings_(initial_settings) 
			{};

			virtual ~GuiDetectionOutput() {};

			// Using default copy and move constructors. 
			GuiDetectionOutput(const GuiDetectionOutput& other) = default;	
			GuiDetectionOutput& operator=(const GuiDetectionOutput& other) = default;
			GuiDetectionOutput(GuiDetectionOutput&& other) noexcept = default;
			GuiDetectionOutput& operator=(GuiDetectionOutput&& other) noexcept = default;
	};

} // namespace gui

 