#include "BufferManager.hpp"

namespace detect{
    void BufferManager::addDetectedCard(const Card& card, const int& detection_frame, const int& max_distance)
    {
        if(this->buffers_.size() == 0)
		{
			this->buffers_.emplace_back(
                CardBuffer<CARD_BUFFER_SIZE>(card, detection_frame)
                );
		}
		else
		{
			// calculate squared distances of card to known buffers
			std::vector<double> squared_distances;
			for(const auto& buffer: this->buffers_)
			{
				squared_distances.emplace_back(
                    templates::squaredEuclideanDistance2D(buffer.getCenter(), card.center_point)
                    );
			}
			// find min distance and add card to that buffer, if the distance is small enough. 
            // Otherwise it is a new card and a new buffer is created
			auto p = std::min_element(squared_distances.begin(), squared_distances.end());
			auto pos = std::distance(squared_distances.begin(), p);
			if( *p < max_distance * max_distance)
			{
				this->buffers_.at(pos).put(card, detection_frame);
			}
			else
			{
				this->buffers_.emplace_back(
                    CardBuffer<CARD_BUFFER_SIZE>(card, detection_frame)
                    );
			}			
		}
    }

    std::vector<Card> BufferManager::getBufferedCards()
    {
        std::vector<Card> cards;
        for(auto p = this->buffers_.begin(); p != this->buffers_.end(); ++p)
		{
			Card card_tmp;
			// only use buffers that were updated in the last 3 frames
			if( (*p).getCard(card_tmp) )
			{				
				cards.emplace_back(card_tmp);
			}
            else
            {
                //do nothing
            }            	
        }

        return cards;
    }

    void BufferManager::removeStaleBuffers(const int& update_threshold, const int& current_frame)
    {
        for(auto p = this->buffers_.begin(); p != this->buffers_.end(); ++p)
		{
			if((*p).getLastUpdate() <= current_frame - update_threshold)
			{				
				// p must be decremented after erase is called, as p is invalidated by erase
				this->buffers_.erase(p--);
			}			
			else
			{
					//do nothing
			}		
		}	
    }
}//end namespace detect