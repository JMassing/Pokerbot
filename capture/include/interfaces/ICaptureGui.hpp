#pragma once

#include "CameraSettings.hpp"

namespace capture
{
	class ICaptureGui
	{
		public:

			virtual capture::CameraSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual ~ICaptureGui() {};
	};

}//end namespace interfaces


