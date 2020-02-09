#pragma once

#include <vector>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "Card.h"
#include "Mapping.h"

namespace detect {

	class View
	{
	public:
		View();
		~View();

		void drawCards(const std::vector<Card> cards, cv::Mat& dst, const cv::Scalar& color);
	private:

		std::map<std::string, int> card_mappings_;

		void showImages(std::vector<cv::Mat> Images);
		void drawContours(const std::vector<std::vector<cv::Point> >& contours, const cv::Mat& dst,const cv::Scalar& color);
		//void drawPoints(const cv::Mat& src, const cv::Scalar& color);
		void writeCard(const cv::Mat& src, const std::vector<Card>& cards);

	};

} // namespace visualize

