#pragma once

// Interface for camera controller

#include "CameraSettings.hpp"

namespace capture {

	class ICameraDevice
	{ 
		public:
			
			virtual bool initCamera(const CameraSettings& camera_settings) = 0;
			virtual bool grabLive() = 0;
			virtual void setCameraControls(const CameraSettings& camera_settings) = 0;

			virtual ~ICameraDevice() {};
			
	};

} //end namespace capture

