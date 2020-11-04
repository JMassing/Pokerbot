#pragma once

#include <utility>
#include <array>
#include <algorithm>

#include "Card.hpp"
#include "BaseCard.hpp"
#include "RingBuffer.hpp"
#include "Image.hpp"

// The card buffer is used to account for outliers in the detection.
// We always compare a sample of the N-1 last detections with the current detection of the card. 
// If the current detection has changed, this is first considered an outlier. 
// However, it might be the case, that the card was initially detected as unknown or something 
// wrong for a different reason. After some time the new and right detections 
// take over the buffer and we return the right card. 

namespace detect
{	

	template<std::size_t N>
	class CardBuffer: public templates::RingBuffer<BaseCard, N>
	{	
		
	private:

		cv::Point center_point_;
		std::vector<cv::Point> contour_;
		Image card_image_;
		Image rank_image_;
		Image suit_image_;

		bool filled_once_;
		int last_update_;

	public:


		bool getCard(Card& card_out);
		
		// Override put function for card buffer to also update center point and 
		// contour with the center point and contour of the latest card
		void put(const Card& card_in, const int& frame_nr);
		cv::Point getCenter() const
		{
			return this->center_point_;
		}
		std::vector<cv::Point> getContour() const
		{
			return this->contour_;
		}

		int getLastUpdate() const
		{
			return this->last_update_;
		}

		explicit CardBuffer(int frame_nr) :
			templates::RingBuffer<BaseCard,N>::RingBuffer(), 
			center_point_(), 
			filled_once_(false), 
			contour_(), 
			last_update_(frame_nr),
			card_image_(), 
			rank_image_(), 
			suit_image_() 
			{};
		CardBuffer(const Card& card, int frame_nr) : templates::RingBuffer<BaseCard,N>::RingBuffer(), filled_once_(false) 
		{
			this->put(card, frame_nr);
		};
	
		CardBuffer(const CardBuffer& other) = default;	
		CardBuffer& operator=(const CardBuffer& other) = default;
		CardBuffer(CardBuffer&& other) noexcept = default;
		CardBuffer& operator=(CardBuffer&& other) noexcept = default;
		
	};

	template<std::size_t N>
	void CardBuffer<N>::put(const Card& card_in, const int& frame_nr)
	{
		templates::RingBuffer<BaseCard,N>::put(card_in);
		this->center_point_ = card_in.center_point;
		this->contour_ = card_in.contour;
		this->last_update_ = frame_nr;
		this->card_image_ = card_in.card_image;
		this->rank_image_ = card_in.rank_image;
		this->suit_image_ = card_in.suit_image;

		if(this->full())
		{ 
			this->filled_once_ = true;
		}
	};
	
	template<std::size_t N>
	bool CardBuffer<N>::getCard(Card& card_out)
	{

		// Find the card that is occuring most often in the buffer
		std::vector<std::pair<BaseCard, int> > card_counter;
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
					// if card is not found in card_counter add it to counter
					if(p == card_counter.end()-1)
					{
						card_counter.emplace_back(std::make_pair(card, 1));
						break;
					}					
				}
			}
				
		}
		// sort card_counter for highest amount of cards
		std::sort(card_counter.begin(), card_counter.end(), 
				  [](const auto& lhs, const auto& rhs){ return lhs.second > rhs.second; }
       			);
		card_out.rank = card_counter.at(0).first.rank;
		card_out.suit = card_counter.at(0).first.suit;
		card_out.center_point = this->center_point_;
		card_out.contour = this->contour_;
		card_out.card_image = this->card_image_;
		card_out.suit_image = this->suit_image_;
		card_out.rank_image = this->rank_image_;
			
		return true;
	
	};
}