#pragma once

// Interface for card detector

#include <vector>

#include "Image.hpp"
#include "Card.hpp"

namespace detect {

	/** *\ingroup detection
	* @class ICardDetector
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface which defines minimum required functionality for card detection class. 
	*		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/	

	class ICardDetector
	{ 
		public:
			
			virtual void detectCards() = 0;
			virtual const std::vector<Card> getCards() = 0; 
			virtual void updateFrame() = 0;

			virtual ~ICardDetector() {};			
	};

} //end namespace capture

