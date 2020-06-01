#pragma once

#include <vector>
#include <string>
#include <array>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "TrainImage.h"
#include "Card.h"
#include "Mapping.h"
#include "CardBuffer.h"
#include "CompiletimeConstants.h"
#include "TemplateFunctions.h"
#include "DataDetectGui.h"
#include "DataPokerDetect.h"


namespace detect 
{

	class CardDetector
	{

		private:
			enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };

			cv::Mat live_frame_;
			std::vector<Card> cards_;
			std::vector<CardBuffer<globals::CARD_BUFFER_SIZE>> card_buffers_;
			std::shared_ptr<data::DataDetectGui> data_gui_;
			std::shared_ptr<data::DataPokerDetect> data_poker_;

			int frame_nr_;
			
			const double aspect_ratio_ = 1.4;									 // Aspect Ratio of playing cards
			const int card_width_ = 301;										 // Nr. of cols in extracted card image							 
			const std::array<int, 11> sliding_threshold_
				{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };						 // arrays of values for sliding threshold for binaryzing image
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
			void bufferCard(const Card& card);
			bool isInArea(const Card& card, const cv::Rect& area);
			void assignCards();

		public:

			void detectCards();
			const std::vector<Card> getCards() { return this->cards_; }
			void updateFrame(const cv::Mat& input_frame);
			CardDetector(std::shared_ptr<data::DataDetectGui>& data_gui, std::shared_ptr<data::DataPokerDetect>& data_poker);
			~CardDetector();

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;
			

		
	};

}//namespace detect
