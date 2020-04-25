#pragma once
#include <vector>
#include <string>
#include <array>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "TrainImage.h"
#include "Card.h"
#include "Mapping.h"

namespace detect 
{

	class CardDetector
	{

		private:
			enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };

			cv::Mat live_frame_;
			std::vector<Card> cards_;
			
			const double aspect_ratio_ = 1.4;									 // Aspect Ratio of playing cards
			const int card_width_ = 301;										 // Nr. of cols in extracted card image
			const int live_threshold_ = 40;										 // threshold added to mean image intensity for finding cards in live image (cards are brighter than background, so +)
			const int card_threshold_ = -10;									 // threshold added to mean image intensity for finding the rank and suit in the card image (rank and suit are darker than card image, so -)
			const int binary_threshold_ = 0;									 // threshold added to mean image intensity for binaryzing suit and rank image (rank and suit edges are close to mean image intensity, so 0);
			const std::array<int, 15> sliding_threshold_
				{-17, -15, -12 , -10, -7, -5, -2, 0, 2, 5, 7, 10, 12, 15, 17 };	 // arrays of values for sliding threshold for binaryzing image
			const int min_card_size_ = 10000;									 // Min size card image in pixel²
			const int max_card_size_ = 200000;									 // Max size card image in pixel²
			const double min_comparison_confidence_ = 5;						 // Maximum l2 error allowed for compareImages. If error is higher, card is marked as unknown
			std::vector<TrainImage> train_suits_;
			std::vector<TrainImage> train_ranks_;

			void loadTrainImages(const std::string &path, std::vector<TrainImage>& train_images);		
			void contourFilter(std::vector<std::vector<cv::Point> >& contour, int method = LARGEST_AREA, double value = 0);	 
			void calculateCornerPoints(const std::vector<std::vector<cv::Point> >& contours, std::vector < std::vector< cv::Point2f >>& corners);	// calculates corners of card
			void calculateCenterPoint(const std::vector<std::vector<cv::Point> >& contours, std::vector< cv::Point2f >& centers);					// calculates center point of card
			bool perspectiveTransformation(const cv::Mat src, cv::Mat& dst, const std::vector< cv::Point2f >& points);
			std::vector< cv::Point2f > sortCorners(std::vector< cv::Point2f > points, cv::Point2f center);
			void identifyCard(Card& card, const cv::Mat& card_image);
			void binarizeImage(const cv::Mat & src, cv::Mat & dst, const int& threshold, const int& thresh_method);
			double compareImages(const cv::Mat &src, const cv::Mat &dst);
			void findContours(const cv::Mat& src, std::vector<std::vector<cv::Point> >& contours, const int& threshold, const int& thresh_method = cv::THRESH_BINARY);

		public:
			explicit CardDetector(const cv::Mat& input_frame);
			~CardDetector();

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;
			
			void detectCards();
			const std::vector<Card> getCards() { return this->cards_; }
		
	};

}//namespace detect
