#pragma once

#include <memory>
#include <DefaultConfig.h>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

namespace shared
 {

	struct CameraControls
	{ 		    
		public:

 			int device_ID;
            bool auto_exposure;
            bool auto_focus;
			bool auto_wb;
            int exposure_time;
            int brightness;
            int focus;
            int zoom;
			int image_width;
			int image_height;
			std::shared_ptr<DefaultConfig> default_config;

			void setToDefault()
			{
				this->device_ID = default_config->device_ID;
				this->auto_exposure = default_config->auto_exposure;
				this->auto_focus = default_config->auto_focus;
				this->auto_wb = default_config->auto_wb;
				this->exposure_time = default_config->exposure_time;
				this->brightness = default_config->brightness;
				this->focus = default_config->focus;
				this->zoom = default_config->zoom;
				this->image_width = default_config->image_width;
				this->image_height = default_config->image_height;
			}

			void saveAsDefault()
			{
				default_config->device_ID = this->device_ID;
				default_config->auto_exposure = this->auto_exposure;
				default_config->auto_focus = this->auto_focus;
				default_config->auto_wb = this->auto_wb;
				default_config->exposure_time = this->exposure_time;
				default_config->brightness = this->brightness; 
				default_config->focus = this->focus;
				default_config->zoom = this->zoom;
				default_config->image_width = this->image_width;
				default_config->image_height = this->image_height;
				this->default_config->saveConfig();
			}

			CameraControls(std::shared_ptr<DefaultConfig>& default_config): default_config(default_config)
			{
				this->setToDefault();
			};
			~CameraControls(){};

			// Using default copy and move constructors. 
			CameraControls(const CameraControls& other) = default;	
			CameraControls& operator=(const CameraControls& other) = default;
			CameraControls(CameraControls&& other) noexcept = default;
			CameraControls& operator=(CameraControls&& other) noexcept = default;
			
	};
}//end namespace data

