#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Card.h"

namespace detect
{
	class CardBuffer
	{
	private:
		static int id_;
		std::array<Card,100> buffer_;
		int pos_tracker_;
		cv::Point center_point_;

	public:
		
		void addCard(Card& card);

		int getId()
		{ 
			return this->id_; 
		}

		CardBuffer(): center_point_{}, pos_tracker_{0} 
		{
			++id_;
			this->buffer_.fill(Card(-1,-1));
		};

		~CardBuffer()
		{

		};

		// Use Default copy and move constructors
		CardBuffer(const CardBuffer& other) = default;	
		CardBuffer& operator=(const CardBuffer& other) = default;
		CardBuffer(CardBuffer&& other) noexcept = default;
		CardBuffer& operator=(CardBuffer&& other) noexcept = default;
		
	};
	int CardBuffer::id_ = 0;

}