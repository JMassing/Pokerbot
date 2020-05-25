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

		// Use Default copy and move constructors
		Card(const Card& other) = default;	
		Card& operator=(const Card& other) = default;
		Card(Card&& other) noexcept = default;
		Card& operator=(Card&& other) noexcept = default;
		
	};

}