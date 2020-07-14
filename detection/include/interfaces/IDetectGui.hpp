#pragma once

#include <vector>

#include "ImProcSettings.hpp"
#include "Card.hpp"

namespace detect
{
	class IDetectGui
	{
		public:

			virtual ImProcSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual void setCards(std::vector<Card> cards) = 0;
			virtual ~IDetectGui() {};
	};

}//end namespace interfaces


