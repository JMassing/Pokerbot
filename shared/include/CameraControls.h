#pragma once

#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "DefaultConfig.h"

namespace shared
 {

	struct CameraControls
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

			void setToDefault(const DefaultConfig& default_settings)
			{
				 this->auto_exposure = default_settings.auto_exposure;
				 this->auto_focus = default_settings.auto_focus;
				 this->auto_wb = default_settings.auto_wb;
				 this->exposure_time = default_settings.exposure_time;
				 this->brightness = default_settings.brightness;
				 this->focus = default_settings.focus;
				 this->zoom = default_settings.zoom;
				 this->image_width = default_settings.image_width;
				this->image_height = default_settings.image_height;
			};

			CameraControls(): auto_exposure(true), auto_focus(true), auto_wb(true), exposure_time(-5), brightness(128), focus(40), zoom(40), image_width(1280), image_height(1024) {};
			~CameraControls(){};

			// Using default copy and move constructors. 
			CameraControls(const CameraControls& other) = default;	
			CameraControls& operator=(const CameraControls& other) = default;
			CameraControls(CameraControls&& other) noexcept = default;
			CameraControls& operator=(CameraControls&& other) noexcept = default;
			
	};
}//end namespace data

