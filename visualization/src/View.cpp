#include "View.h"

#include <iostream>
#include <string>

namespace detect {
	View::View()
	{
	}


	View::~View()
	{
	}

	//@brief: visualize cards in grabbed image. Draws contours and card names
	void View::drawCards(const std::vector<Card> cards, cv::Mat& dst, const cv::Scalar& color)
	{
		cv::Mat drawing = cv::Mat::zeros(dst.size(), CV_8UC3);
		std::vector<std::vector<cv::Point> > contours;
		for (const auto& card : cards)
		{
			contours.emplace_back(card.contour);
		}

		for (int i = 0; i < cards.size(); ++i)
		{
			cv::drawContours(drawing, contours, i, color, 1, 8, cv::noArray(), 0, cv::Point());
		}
		drawing.copyTo(dst, drawing);
		this->writeCard(dst, cards);
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
	void View::drawContours(const std::vector<std::vector<cv::Point> >& contours, const cv::Mat& dst, const cv::Scalar& color)
	{
		cv::Mat drawing = cv::Mat::zeros(dst.size(), CV_8UC3);
		for (int i = 0; i < contours.size(); ++i) {
			cv::drawContours(drawing, contours, i, color, 1, 8, cv::noArray(), 0, cv::Point());
		}
		drawing.copyTo(dst, drawing);
	}

	//@brief: Writes card type into image. Writes approx. into middle of card
	void View::writeCard(const cv::Mat& src, const std::vector<Card>& cards)
	{
		
		std::string rank;
		std::string suit;
		std::string text;
		Mapping mapping;

		for (int i = 0; i < cards.size(); ++i)
		{	
			if (cards[i].suit == UNKNOWN || cards[i].rank == UNKNOWN)
			{
				text = "Unknown";
			}
			else
			{
				rank = mapping.image_mappings.right.at(cards[i].rank);
				suit = mapping.image_mappings.right.at(cards[i].suit);
				text = rank + " of " + suit;
			}
			cv::putText(src, text, cards[i].center_point-cv::Point(85,0), cv::FONT_HERSHEY_PLAIN, 1.25, cv::Scalar(0, 0, 255), 2);
		}

	}

}