#pragma once

#include "CameraSettings.hpp"
#include "Image.hpp"

namespace capture
{
	/**	
	*\ingroup capture
	* @class ICaptureGui
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface which defines communication between capture and GUI module.
	*		 Implemented in GUI module.
	*		
	* @version 1.0
	* @date 2020-11-18
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class ICaptureGui
	{
		public:

			virtual CameraSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual void setImage(const Image& image) = 0;
			virtual ~ICaptureGui() {};
	};

}//end namespace interfaces


