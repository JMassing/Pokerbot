#pragma once

#include <memory>

#include "ICaptureGui.hpp"

namespace gui {

	class GuiCaptureIO: public capture::ICaptureGui
	{
		public:	
			//Camera Controls
			capture::CameraSettings& camera_settings_;
			capture::Image live_image_;
			bool& user_input_;		

            capture::CameraSettings getSettings() const override
			{
				 return this->camera_settings_;
			} 
			
			bool checkUserInput() const override
			{
				return this->user_input_;
			}

			void setImage(const capture::Image& image)
			{
				this->live_image_ = image;
			}

        	explicit GuiCaptureIO(
				capture::CameraSettings& camera_settings,
				bool& input
				): 
				camera_settings_(camera_settings), 
				user_input_(input),
				live_image_{}
			{};

			virtual ~GuiCaptureIO() {};

			// Using default copy and move constructors. 
			GuiCaptureIO(const GuiCaptureIO& other) = default;	
			GuiCaptureIO& operator=(const GuiCaptureIO& other) = default;
			GuiCaptureIO(GuiCaptureIO&& other) noexcept = default;
			GuiCaptureIO& operator=(GuiCaptureIO&& other) noexcept = default;
	};

} // namespace gui

 