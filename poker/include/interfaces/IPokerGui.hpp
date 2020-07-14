#pragma once

#include <vector>

#include "SimSettings.hpp"
#include "DataPoker.hpp"

namespace poker
{
	class IPokerGui
	{
		public:

			virtual SimSettings getSettings() const = 0;
			virtual bool checkUserInput() const = 0;
			virtual void setData(const DataPoker& data) = 0;
			virtual ~IPokerGui() {};
	};

}//end namespace interfaces


