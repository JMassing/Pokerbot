#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Card.h"

namespace detect
{
	struct CardBuffer
	{
		
		std::array<Card,100> buffer;
		
		cv::Point center_point;

		CardBuffer() { };
		~CardBuffer() {};

		// Use Default copy and move constructors
		CardBuffer(const CardBuffer& other) = default;	
		CardBuffer& operator=(const CardBuffer& other) = default;
		CardBuffer(CardBuffer&& other) noexcept = default;
		CardBuffer& operator=(CardBuffer&& other) noexcept = default;
		
	};

}