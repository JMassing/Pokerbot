#pragma once

#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <memory>

#include "Image.h"
#include "TrainImage.h"
#include "Card.h"
#include "Mapping.h"
#include "CardBuffer.h"
#include "Parameters.h"
#include "TemplateFunctions.h"
#include "DataDetectGui.h"
#include "DataPokerDetect.h"
#include "ImProc.h"


namespace detect 
{
	 // CompileTime constants    
	constexpr size_t CARD_BUFFER_SIZE = 10;
    constexpr double MAX_DISTANCE_TO_BUFFER = 200;

	class CardDetector
	{

		private:
			enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };
		  
			Image live_frame_;
			std::vector<Card> cards_;
			std::vector<CardBuffer<CARD_BUFFER_SIZE>> card_buffers_;
			std::shared_ptr<data::DataDetectGui> data_gui_;
			std::shared_ptr<data::DataPokerDetect> data_poker_;
			int frame_nr_;			
			std::vector<TrainImage> train_suits_;
			std::vector<TrainImage> train_ranks_;

			const int card_width_ = 301;										 // Nr. of cols in extracted card image		
			const std::array<int, 11> sliding_threshold_
				{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };						 // arrays of values for sliding threshold for binaryzing image
			const double aspect_ratio_ = 1.4;									 // Aspect Ratio of playing cards
			const int min_card_size_ = 8000;									 // Min size card image in pixel²
			const int max_card_size_ = 500000;									 // Max size card image in pixel²
			const double min_comparison_confidence_ = 5;						 // Maximum l2 error allowed for compareImages. If error is higher, card is marked as unknown					 

			void loadTrainImages(const std::string &path, std::vector<TrainImage>& train_images);			
			void identifyCard(Card& card, const cv::Mat& card_image);
			void bufferCard(const Card& card);
			bool isInArea(const Card& card, const cv::Rect& area);
			void assignCards();

		public:

			void detectCards();
			const std::vector<Card> getCards() { return this->cards_; }
			void updateFrame(const Image& input_frame);
			CardDetector(std::shared_ptr<data::DataDetectGui>& data_gui, std::shared_ptr<data::DataPokerDetect>& data_poker);
			~CardDetector();

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;
					
	};

}//namespace detect
