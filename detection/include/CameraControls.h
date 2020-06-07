#pragma once

#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

namespace detect {

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
						
			bool operator==(const CameraControls &other) const
			{
				return(this->auto_exposure ==  other.auto_exposure && this->auto_focus == other.auto_focus && this->exposure_time == other.exposure_time &&
				this->brightness == other.brightness && this->focus == other.focus && this->zoom == other.zoom && this->image_height == other.image_height &&
				this->image_width == other.image_width && this->auto_wb == other.auto_wb);
			};	

			bool operator!=(const CameraControls &other) const
			{
				return !(*this == other);
			};	

			CameraControls(): auto_exposure(true), auto_focus(true), exposure_time(-5), brightness(128), 
			focus(45), zoom(100), image_width(1280), image_height(720), auto_wb(true)
			{};
			~CameraControls(){};

			// Using default copy and move constructors. 
			CameraControls(const CameraControls& other) = default;	
			CameraControls& operator=(const CameraControls& other) = default;
			CameraControls(CameraControls&& other) noexcept = default;
			CameraControls& operator=(CameraControls&& other) noexcept = default;
			
	};
}

