#pragma once

#include <vector>

#include "Card.hpp"
#include "ImProcSettings.hpp"
#include "Image.hpp"

namespace detect
{
	/** *\ingroup shared
	 * @class IDetectionDataHandler
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Interface for sending/receiving data from/to detection module
	 *		
	 * @version 1.0
	 * @date 2020-12-07
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class IDetectionDataHandler
	{
		public:

			virtual bool getLiveFrame(Image&) const = 0;
			virtual bool getProcessingSettings(ImProcSettings&) = 0;
			virtual bool sendDetectedCards(const std::vector<Card>&) const = 0;		
			virtual ~IDetectionDataHandler() {};
	};
}
