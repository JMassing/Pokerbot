#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>


namespace detect {

	struct CameraControls
	{ 		            
            bool auto_exposure;
            bool auto_focus;
            int exposure_time;
            int brightness;
            int focus;
            int zoom;
			int image_width;
			int image_height;

			bool operator==(const CameraControls &b) const
			{
				if(this->auto_exposure != b.auto_exposure || this->auto_focus != b.auto_focus || this->exposure_time != b.exposure_time || this->brightness != b.brightness ||
				this->focus != b.focus || this->zoom != b.zoom || this->image_height != b.image_height || this->image_width != b.image_width )
				{
					return false;
				}
				return true;
			};	

			bool operator!=(const CameraControls &b) const
			{
				if(this->auto_exposure != b.auto_exposure || this->auto_focus != b.auto_focus || this->exposure_time != b.exposure_time || this->brightness != b.brightness ||
				this->focus != b.focus || this->zoom != b.zoom || this->image_height != b.image_height || this->image_width != b.image_width)
				{
					return true;
				}
				return false;
			};	

			CameraControls(): auto_exposure(true), auto_focus(true), exposure_time(-5), brightness(128), focus(45), zoom(100), image_width(1280), image_height(720) {};
			~CameraControls(){};

			// Using default copy and move constructors. 
			CameraControls(const CameraControls& other) = default;	
			CameraControls& operator=(const CameraControls& other) = default;
			CameraControls(CameraControls&& other) noexcept = default;
			CameraControls& operator=(CameraControls&& other) noexcept = default;
			
	};

}

