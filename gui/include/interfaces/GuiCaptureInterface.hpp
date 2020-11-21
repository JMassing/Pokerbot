#pragma once

#include <memory>

#include "ICaptureGui.hpp"

namespace gui {

	/**
	* @class GuiCaptureInterface
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Implements communication interface between capture and GUI module.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class GuiCaptureInterface: public capture::ICaptureGui
	{
		public:	
			//Camera Controls
			capture::CameraSettings& camera_settings_;
			Image live_image_;
			bool& user_input_;		

            capture::CameraSettings getSettings() const override
			{
				 return this->camera_settings_;
			} 
			
			bool checkUserInput() const override
			{
				return this->user_input_;
			}

			void setImage(const Image& image)
			{
				this->live_image_ = image;
			}

        	explicit GuiCaptureInterface(
				capture::CameraSettings& camera_settings,
				bool& input
				): 
				camera_settings_(camera_settings), 
				user_input_(input),
				live_image_{}
			{};

			virtual ~GuiCaptureInterface() {};

			// Using default copy and move constructors. 
			GuiCaptureInterface(const GuiCaptureInterface& other) = default;	
			GuiCaptureInterface& operator=(const GuiCaptureInterface& other) = default;
			GuiCaptureInterface(GuiCaptureInterface&& other) noexcept = default;
			GuiCaptureInterface& operator=(GuiCaptureInterface&& other) noexcept = default;
	};

} // namespace gui

 