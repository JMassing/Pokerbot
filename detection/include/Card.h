#pragma once

#include <opencv2/core.hpp>

#include "BaseCard.h"

namespace detect
{
	struct Card: public BaseCard
	{
	
		cv::Point center_point;
		std::vector<cv::Point> contour;
		cv::Mat card_image;
		cv::Mat rank_image;
		cv::Mat suit_image;

		Card() : BaseCard(), center_point(-1, -1), contour{} { };
		Card(const int& rank, const int& suit) : BaseCard(rank, suit), center_point(-1, -1), contour{} { };
		Card(const int& rank, const int& suit, const cv::Point& center, const std::vector<cv::Point>& contour) : BaseCard(rank,suit), 
			center_point(center), contour{contour} { };
		~Card() {};

		// Make sure we do a deep copy when we use copy constructors. Otherwise we might be surprised at some point, when doing changes to the image data.
		Card(const Card& other) noexcept : BaseCard(), center_point{}, contour{}, card_image{}, rank_image{}, suit_image{}
		{
			// use copy assignment operator as defined below
			*this = other;
		};	
		Card& operator=(const Card& other) noexcept
		{
			if (this != &other)
			{
				this->rank = other.rank;
				this->suit = other.suit;
				this->center_point = other.center_point;
				this->contour = other.contour;
				this->card_image = other.card_image.clone();
				this->rank_image = other.rank_image.clone();
				this->suit_image = other.suit_image.clone();
			}
			return *this;
		};
		
		// Use custom move constructors to make sure, images are released
		Card(Card&& other) noexcept : BaseCard(), center_point{}, contour{}, card_image{}, rank_image{}, suit_image{}
		{
			// use move assignment operator as defined below
			*this = std::move(other);
		};
		Card& operator=(Card&& other) noexcept
		{
			if (this != &other)
			{
				//Free the existing images 
				this->card_image.release();
				this->suit_image.release();
				this->rank_image.release();
				
				// assignment operator for cv::Mat returns a pointer to the object, and not a deep copy
				this->card_image = other.card_image;
				this->rank_image = other.rank_image;
				this->suit_image = other.suit_image;

				this->rank = other.rank;
				this->suit = other.suit;
				this->center_point = other.center_point;
				this->contour.swap(other.contour);

				// releasing the old images here will decrement the ref counter, but not delete the underlying data. Other.image will point to NULL
				other.card_image.release();
				other.rank_image.release();
				other.suit_image.release();	
			}
			return *this;
		};		
	};

} //end namespace detect