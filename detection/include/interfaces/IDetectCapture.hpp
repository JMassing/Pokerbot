#pragma once

#include "Image.hpp"

namespace detect
{
	class IDetectCapture
	{
		public:
            
			virtual Image getImage() const = 0;

			virtual ~IDetectCapture() {};
	};

}//end namespace interfaces


