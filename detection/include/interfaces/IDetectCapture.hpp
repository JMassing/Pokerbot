#pragma once

#include "Image.hpp"

namespace detect
{
	/**
	* @class IDetectCapture
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface which defines communication between capture and detection module.
	*		 Implemented in capture module.
	*		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class IDetectCapture
	{
		public:
            
			virtual Image getImage() const = 0;

			virtual ~IDetectCapture() {};
	};

}//end namespace interfaces


