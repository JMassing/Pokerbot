#pragma once

#include <iostream>

#include "BaseCard.hpp"
#include "Image.hpp"

namespace detect
{
	/**
	* @class Card
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Data Structure for detected cards. 
	* Extends BaseCard with the detected center_point and card contour and card, rank and suit images
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	struct Card: public BaseCard
	{
	
		cv::Point center_point;
		std::vector<cv::Point> contour;
		Image card_image;
		Image rank_image;
		Image suit_image;

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