#pragma once


#include "CameraSettings.hpp"

namespace capture {

	/**
	*\ingroup capture
	* @class ICameraController
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface which defines minimum required functionality for camera control. 
	*		
	* @version 1.0
	* @date 2020-11-18
	* 
	* @copyright Copyright (c) 2020
	* 
	*/	
	class ICameraController
	{ 
		public:
			
			virtual bool initCamera(const CameraSettings& camera_settings) = 0;
			virtual bool grabLive() = 0;
			virtual void setCameraControls(const CameraSettings& camera_settings) = 0;

			virtual ~ICameraController() {};
			
	};

} //end namespace capture

