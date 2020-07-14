#pragma once

#include "CameraSettings.hpp"
#include "Image.hpp"

namespace capture
{
	class ICaptureGui
	{
		public:

			virtual CameraSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual void setImage(const Image& image) = 0;
			virtual ~ICaptureGui() {};
	};

}//end namespace interfaces


