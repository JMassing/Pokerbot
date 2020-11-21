#pragma once

#include <vector>

#include "ImProcSettings.hpp"
#include "Card.hpp"

namespace detect
{
	/**
	* @class IDetectGui
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface which defines communication between gui and detection module.
	*		 Implemented in gui module.
	*		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class IDetectGui
	{
		public:

			virtual ImProcSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual void setCards(std::vector<Card> cards) = 0;
			virtual ~IDetectGui() {};
	};

}//end namespace interfaces


