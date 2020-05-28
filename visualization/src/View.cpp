#include "View.h"

#include <iostream>
#include <string>

namespace visualization {
	View::View(): color_(0, 255, 0)
	{
	}


	View::~View()
	{
	}

	//@brief: visualize cards in grabbed image. Draws contours and card names
	void View::drawCards(const std::vector<detect::Card>& cards, cv::Mat& dst)
	{
		std::vector<std::vector<cv::Point> > contours;
		for (const auto& card : cards)
		{
			// make sure card has a contour
			if(card.contour.size() > 0)
			{
				contours.emplace_back(card.contour);
			}
		}
		
		//
		if(contours.size() > 0)
		{
			this->drawContours(contours, dst, this->color_);
			this->writeCard(dst, cards);
		}
		
	}

	//@brief: Show grabbed images
	void View::showImages(std::vector<cv::Mat> images)
	{
		int i = 1;
		for (auto const& image : images)
		{
			cv::imshow("Image" + std::to_string(i), image);
			++i;
		}
	}

	//@brief: Draw given contour into given image 
	void View::drawContours(const std::vector<std::vector<cv::Point> >& contours, cv::Mat& dst, const cv::Scalar& color)
	{
		cv::Mat drawing = cv::Mat::zeros(dst.size(), CV_8UC3);
		for (int i = 0; i < contours.size(); ++i) 
		{
			cv::drawContours(drawing, contours, i, color, 1, 8, cv::noArray(), 0, cv::Point());
		}
		drawing.copyTo(dst, drawing);
	
	}

	//@brief: Writes card type into image. Writes approx. into middle of card
	void View::writeCard(cv::Mat& src, const std::vector<detect::Card>& cards)
	{
		
		std::string rank;
		std::string suit;
		std::string text;
		detect::Mapping mapping;

		for (int i = 0; i < cards.size(); ++i)
		{	
			if (cards[i].suit == detect::UNKNOWN || cards[i].rank == detect::UNKNOWN)
			{
				text = "Unknown";
			}
			else
			{
				rank = mapping.image_mappings.right.at(cards[i].rank);
				suit = mapping.image_mappings.right.at(cards[i].suit);
				text = rank + " of " + suit;
			}
			this->printText(src, text, cards[i].center_point-cv::Point(85,0));
		}

	}

	void View::printText(cv::Mat& dst, std::string& text, cv::Point& pos)
	{
		cv::putText(dst, text, pos, cv::FONT_HERSHEY_PLAIN, 1.25, cv::Scalar(0, 0, 255), 2);
	}
	void View::printProbability(const cv::Mat& src, const std::pair<double,double>& probability)
	{
		std::string winning_probability;
		std::string tie_probability;
		winning_probability = "Winning: " + std::to_string(probability.first) + "%";
		tie_probability = "Winning Tie: " + std::to_string(probability.second) + "%";

		cv::putText(src, winning_probability, cv::Point(30,50), cv::FONT_HERSHEY_PLAIN, 1.25, cv::Scalar(255, 0, 0), 2);
		cv::putText(src, tie_probability, cv::Point(30,70), cv::FONT_HERSHEY_PLAIN, 1.25, cv::Scalar(255, 0, 0), 2);

	}

	void View::show(cv::Mat& frame, const std::vector<detect::Card> cards, const std::pair<double,double>& probability )
	{
		if(cards.size() > 0)
		{
			this->drawCards(cards, frame);
			this->printProbability(frame, probability);
		}

		cv::Mat live_img = this->resize(frame, 1024, 600);
		imshow("live", live_img);
	}

	cv::Mat View::resize(const cv::Mat& frame, const int& width, const int& height)
	{
		cv::Mat live_img;
		live_img.create(cv::Size(width, height), frame.type());
		cv::resize(frame, live_img, live_img.size(), 0, 0, cv::INTER_LINEAR); 
		return live_img;
	}

	void View::drawRectangle(cv::Mat& frame, const cv::Point& pt, const int& width, const int& height)
	{
		cv::Rect rect(pt.x, pt.y, width, height);	
		cv::rectangle(frame, rect, cv::Scalar{255, 0, 0}, 3);
	}


}