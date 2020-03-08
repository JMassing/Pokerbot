#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Mapping.h"


namespace detect
{
	struct Card
	{
		int rank;
		int suit;
		cv::Point center_point;
		std::vector<cv::Point> contour;

		Card() : rank(UNKNOWN), suit(UNKNOWN), center_point(-1, -1), contour{} {};
		Card(int rank, int suit) :rank(rank), suit(suit), center_point(-1, -1), contour{} {};
		Card(int rank, int suit, cv::Point center, std::vector<cv::Point> contour) :rank(rank), suit(suit), center_point(center), contour{contour} {};
		~Card() {};

		bool operator==(const Card& other) const
		{
			// if suit and rank are equal, the cards are the same cards, since there is only one copy of each card in the deck.
			return (this->rank == other.rank && this->suit == other.suit);
		};
		// Using default copy and move constructors. 
		Card(const Card& other) = default;	
		Card& operator=(const Card& other) = default;
		Card(Card&& other) noexcept = default;
		Card& operator=(Card&& other) noexcept = default;
		
	};

}