#pragma once

#include <vector>

#include "GameSettings.hpp"
#include "DataPoker.hpp"

namespace poker
{
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


