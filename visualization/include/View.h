#pragma once

#include <vector>
#include <utility>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "Card.h"
#include "Mapping.h"

namespace visualization {

	class View
	{
		protected:

			void showImages(std::vector<cv::Mat> Images);
			void drawContours(const std::vector<std::vector<cv::Point> >& contours, cv::Mat& dst,const cv::Scalar& color);	
			//void drawPoints(const cv::Mat& src, const cv::Scalar& color);
			void writeCard(cv::Mat& src, const std::vector<detect::Card>& cards, const cv::Scalar& color);
			void printProbability(const cv::Mat& src, const std::pair<double,double>& probability);

		public:
			
			void show(cv::Mat& frame, const std::vector<detect::Card> cards, const std::pair<double,double>& probability, const cv::Scalar& color);
			cv::Mat resize(const cv::Mat& frame, const int& width, const int& height);
			void drawCards(const std::vector<detect::Card>& cards, cv::Mat& dst, const cv::Scalar& color);
			void drawRectangle(cv::Mat& frame, const cv::Rect& rect, const cv::Scalar& color);
			void printText(cv::Mat& dst, std::string& text, cv::Point& pos, const cv::Scalar& color);

			View() {};
			~View() {};

			// Using default copy and move constructors. 
			View(const View& other) = default;	
			View& operator=(const View& other) = default;
			View(View&& other) noexcept = default;
			View& operator=(View&& other) noexcept = default;
	};

} // namespace visualization

