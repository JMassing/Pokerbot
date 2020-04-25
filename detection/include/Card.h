#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "BaseCard.h"

namespace detect
{
	struct Card: public BaseCard
	{
	
		cv::Point center_point;
		std::vector<cv::Point> contour;
		int id;

		Card() : BaseCard(), center_point(-1, -1), contour{}, id{0} { };
		Card(const int& rank, const int& suit) : BaseCard(rank, suit), center_point(-1, -1), contour{}, id{0} { };
		Card(const int& rank, const int& suit, const cv::Point& center, const std::vector<cv::Point>& contour) : BaseCard(rank,suit), center_point(center), contour{contour}, id{0} { };
		~Card() {};

		// Use Default copy and move constructors
		Card(const Card& other) = default;	
		Card& operator=(const Card& other) = default;
		Card(Card&& other) noexcept = default;
		Card& operator=(Card&& other) noexcept = default;
		
	};

}