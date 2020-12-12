#pragma once

#include <vector>

#include "GameSettings.hpp"
#include "DataPoker.hpp"

namespace poker
{
	/**  \ingroup poker
	 * @class IPokerGui
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Interface which defines communication between poker and GUI  module.
	 *		 Implemented in GUI module.
	 *		
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */	
	class IPokerGui
	{
		public:

			virtual GameSettings getSettings() const = 0;
			virtual void setSettings(GameSettings&) = 0;
			virtual bool checkUserInput() const = 0;
			virtual void setData(const DataPoker& data) = 0;
			virtual DataPoker getData() = 0;
			virtual ~IPokerGui() {};
	};

}//end namespace interfaces


