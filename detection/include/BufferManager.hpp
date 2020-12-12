#pragma once

#include <vector>

#include "TemplateFunctions.hpp"
#include "Card.hpp"
#include "CardBuffer.hpp"

namespace detect 
{
    // CompileTime constants    
	constexpr size_t CARD_BUFFER_SIZE = 30;
    /** *\ingroup detection
	 * @class BufferManager
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Manages CardBuffers. Keeps track of new Buffers, adds new detected cards to the corresponding buffer, removes stale Buffers 
     * and returns the detected cards.  
     *  		
	 * @version 1.0
	 * @date 2020-12-12
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class BufferManager
	{
        private:

            std::vector<CardBuffer<CARD_BUFFER_SIZE>> buffers_;

		public:

            /**
             * @brief Adds detected card to corresponding CardBuffer and updates the frame when
             * the corresponding buffer was last updated. To find a corresponding buffer, the 
             * distance of the detected card's position in the image (card center-point) to the 
             * position of the already buffered cards is calculated. The card will be added to the
             * buffer with the min distance if it is within a given maximum. Otherwise it is 
             * considered as a new buffer.
             * 
             * @param card Card to add
             * @param detection_frame Frame nr when card was detected
             * @param max_distance Max distance
             */
            void addDetectedCard(const Card& card, const int& detection_frame, const int& max_distance);
            /**
             * @brief Get the Buffered Cards 
             * 
             * @return std::vector<Card> 
             */
            std::vector<Card> getBufferedCards();
            /**
             * @brief Removes buffers that have not been updated in the last nr frames
             * given in update_threshold
             * 
             * @param update_threshold 
             * @param current_frame 
             */
            void removeStaleBuffers(const int& update_threshold, const int& current_frame);

			BufferManager(){};
			~BufferManager(){};

			// Using default copy and move constructors. 
			BufferManager(const BufferManager& other) = default;	
			BufferManager& operator=(const BufferManager& other) = default;
			BufferManager(BufferManager&& other) noexcept = default;
			BufferManager& operator=(BufferManager&& other) noexcept = default;				
	};
}//namespace detect