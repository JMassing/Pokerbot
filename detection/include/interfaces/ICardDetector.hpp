#pragma once

// Interface for card detector

#include <vector>

#include "Image.hpp"
#include "Card.hpp"

namespace detect {

	class ICardDetector
	{ 
		public:
			
			virtual void detectCards() = 0;
			virtual const std::vector<Card> getCards() = 0; 
			virtual void updateFrame(const Image& input_frame) = 0;

			virtual ~ICardDetector() {};			
	};

} //end namespace capture

