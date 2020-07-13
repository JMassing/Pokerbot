#pragma once

#include "ImProcSettings.hpp"

namespace detect
{
	class IDetectGui
	{
		public:

			virtual detect::ImProcSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual ~IDetectGui() {};
	};

}//end namespace interfaces


