#pragma once

#include <iostream>

#include "BaseCard.h"
#include "Image.h"

namespace detect
{
	struct Card: public BaseCard
	{
	
		cv::Point center_point;
		std::vector<cv::Point> contour;
		capture::Image card_image;
		capture::Image rank_image;
		capture::Image suit_image;

		Card() : BaseCard(), center_point(-1, -1), contour{} { };
		Card(
			const int& rank, 
			const int& suit
			): 
			BaseCard(rank, suit), 
			center_point(-1, -1), 
			contour{} 
			{ };
		Card(
			const int& rank, 
			const int& suit, 
			const cv::Point& center, 
			const std::vector<cv::Point>& contour
			): 
			BaseCard(rank,suit), 
			center_point(center), 
			contour{contour} 
			{ };
		~Card() {};

		// Using default copy and move constructors. 
		Card(const Card& other) = default;
		Card& operator=(const Card& other) = default;
		Card(Card&& other) noexcept = default;
		Card& operator=(Card&& other) noexcept = default;
				
	};

} //end namespace detect