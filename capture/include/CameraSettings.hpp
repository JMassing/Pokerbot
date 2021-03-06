#pragma once

#include "DefaultConfig.hpp"

namespace capture
{
	/**
	 *\ingroup capture
	 * @class CameraSettings
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Data Structure containing Camera Settings
	 *
	 * @version 1.0
	 * @date 2020-11-18
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	struct CameraSettings
	{ 		    
		public:

			bool auto_exposure;
			bool auto_focus;
			bool auto_wb;
			int exposure_time;
			int brightness;
			int focus;
			int zoom;
			int image_width;
			int image_height;
			int wb_temperature;

			/**
			 * @brief Sets the Camera Settings to default values. Method is called on first camera initialization
			 *  	  and when user presses the "set to default button" in the gui.
			 * 
			 * @param default_settings Default values for camera settings. 
			 */
			void setToDefault(const DefaultConfig& default_settings)
			{
				this->auto_exposure = default_settings.auto_exposure;
				this->auto_focus = default_settings.auto_focus;
				this->auto_wb = default_settings.auto_wb;
				this->exposure_time = default_settings.exposure_time;
				this->brightness = default_settings.brightness;
				this->focus = default_settings.focus;
				this->zoom = default_settings.zoom;
				this->wb_temperature = default_settings.wb_temperature;
				this->image_width = default_settings.image_width;
				this->image_height = default_settings.image_height;
			};

			bool operator==(const CameraSettings& other) const
			{
				return 
				(
					this->auto_exposure == other.auto_exposure 	&& 
					this->auto_focus == other.auto_focus 	&&
					this->auto_wb == other.auto_wb	&&
					this->exposure_time == other.exposure_time	&&
					this->brightness == other.brightness	&&
					this->focus == other.focus	&&
					this->zoom == other.zoom	&&
					this->wb_temperature == other.wb_temperature &&
					this->image_width == other.image_width &&
					this->image_height == other.image_height 
				);
			};

			bool operator!=(const CameraSettings& other) const
			{
				return 
				(
					this->auto_exposure != other.auto_exposure 	||
					this->auto_focus != other.auto_focus 	||
					this->auto_wb != other.auto_wb	||
					this->exposure_time != other.exposure_time	||
					this->brightness != other.brightness	 ||
					this->focus != other.focus	||
					this->zoom != other.zoom	||
					this->wb_temperature != other.wb_temperature ||
					this->image_width != other.image_width ||
					this->image_height != other.image_height 
				);
			};

			CameraSettings(): 
			auto_exposure(true), 
			auto_focus(true), 
			auto_wb(true), 
			exposure_time(-5), 
			brightness(128), 
			focus(40), 
			zoom(40), 
			image_width(1280), 
			image_height(1024),
			wb_temperature(4000)
			{};

			~CameraSettings(){};

			// Using default copy and move constructors. 
			CameraSettings(const CameraSettings& other) = default;	
			CameraSettings& operator=(const CameraSettings& other) = default;
			CameraSettings(CameraSettings&& other) noexcept = default;
			CameraSettings& operator=(CameraSettings&& other) noexcept = default;			
	};
	
} //end namespace capture

