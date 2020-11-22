#pragma once

#include "DataDetect.hpp"

namespace poker
{
	/**  \ingroup poker
	* @class IPokerDetect
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface which defines communication between poker and detection module.
	*		 Implemented in detection module.
	*		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/	
	class IPokerDetect
	{
		public:

			virtual detect::DataDetect getData() const = 0;
			virtual ~IPokerDetect() {};
	};

}//end namespace interfaces


