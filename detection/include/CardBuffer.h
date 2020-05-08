#pragma once

#include <utility>
#include <array>
#include <algorithm>

#include "Card.h"
#include "RingBuffer.h"

namespace detect
{	
	// The card buffer is used to account for outliers in the detection. We always compare a sample of the N-1 last detections with the current detection of the card. 
	// If the current detection has changed, this is first considered an outlier. However, it might be the case, that the card was initially detected as unknown or something 
	// wrong for a different reason. After some time the new and right detections take over the buffer and we return the right card.

	template<std::size_t N>
	class CardBuffer: public templates::RingBuffer<Card, N>
	{	
	private:
		int id_;
		cv::Point center_point_;
		bool filled_once_;

	public:

		void getCard(Card& card_out);

		CardBuffer() : RingBuffer(), id_(0), center_point_(), filled_once_(false) {};
	
		// Use Default copy and move constructors
		CardBuffer(const CardBuffer& other) = default;	
		CardBuffer& operator=(const CardBuffer& other) = default;
		CardBuffer(CardBuffer&& other) noexcept = default;
		CardBuffer& operator=(CardBuffer&& other) noexcept = default;
		
	};

	template<std::size_t N>
	void CardBuffer<N>::getCard(Card& card_out)
	{
		// Wait till the buffer was filled at least once, before returning a card. 
		// This way we always have a sample of N detections, to compare 
		if(full() && filled_once_ == false)
		{
			this->filled_once_=true;
		}
		else
		{
			//do nothing
		}
		
		if(this->filled_once_ == true)
		{
			// Find the card that is occuring most often in the buffer
			std::vector<std::pair<Card, int> > card_counter;
			for(const auto& card: this->data_)
			{
				if(card_counter.size() == 0)
				{
					card_counter.emplace_back(std::make_pair(card, 1));
				}
				else
				{
					for( auto p = card_counter.begin(); p != card_counter.end(); ++p)
					{
						//if card is in card counter, increase counter
						if(card == (*p).first)
						{
							++(*p).second;
							break;
						}
						// if card is not found in card_counter add it
						if(p == card_counter.end()-1)
						{
							card_counter.emplace_back(std::make_pair(card, 1));
							break;
						}					
					}
				}
				
			}
			// sort card_counter for highest amount of cards
			std::sort(card_counter.begin(), card_counter.end(), [](const auto& lhs, const auto& rhs)
				{
					return lhs.second > rhs.second;
				}
       		);
			card_out = card_counter.at(0).first;
		}
		else
		{
			//do nothing
		}
	}
}