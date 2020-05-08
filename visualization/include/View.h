#pragma once

#include <vector>
#include <map>
#include <utility>

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
		private:

			std::map<std::string, int> card_mappings_;

			void showImages(std::vector<cv::Mat> Images);
			void drawContours(const std::vector<std::vector<cv::Point> >& contours, const cv::Mat& dst,const cv::Scalar& color);
			//void drawPoints(const cv::Mat& src, const cv::Scalar& color);
			void writeCard(const cv::Mat& src, const std::vector<Card>& cards);
		public:
			
			void drawCards(const std::vector<Card> cards, cv::Mat& dst, const cv::Scalar& color);
			void printProbability(const cv::Mat& src, const std::pair<double,double>& probability);

			View();
			~View();

			// Using default copy and move constructors. 
			View(const View& other) = default;	
			View& operator=(const View& other) = default;
			View(View&& other) noexcept = default;
			View& operator=(View&& other) noexcept = default;
	};

} // namespace visualize

