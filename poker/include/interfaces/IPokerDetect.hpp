#pragma once

#include "DataDetect.hpp"

namespace poker
{
	class IPokerDetect
	{
		public:

			virtual detect::DataDetect getData() const = 0;
			virtual ~IPokerDetect() {};
	};

}//end namespace interfaces


