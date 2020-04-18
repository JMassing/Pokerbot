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

		Card() : BaseCard(), center_point(-1, -1), contour{} { };
		Card(int rank, int suit) : BaseCard(rank, suit), center_point(-1, -1), contour{} { };
		Card(int rank, int suit, cv::Point center, std::vector<cv::Point> contour) : BaseCard(rank,suit), center_point(center), contour{contour} { };
		~Card() {};

		// Use Default copy and move constructors
		Card(const Card& other) = default;	
		Card& operator=(const Card& other) = default;
		Card(Card&& other) noexcept = default;
		Card& operator=(Card&& other) noexcept = default;
		
	};

}