#pragma once

#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <memory>

#include "Image.hpp"
#include "TrainImage.h"
#include "Card.h"
#include "Mapping.h"
#include "CardBuffer.h"
#include "TemplateFunctions.h"
#include "ImProcSettings.h"
#include "DataPokerDetect.h"
#include "ImProc.h"
#include "DefaultConfig.h"


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
			std::shared_ptr<shared::ImProcSettings> data_gui_;
			std::shared_ptr<shared::DataPokerDetect> data_poker_;
			int frame_nr_;			
			std::vector<TrainImage> train_suits_;
			std::vector<TrainImage> train_ranks_;

			int card_width_;										 // Nr. of cols in extracted card image		
			const std::array<int, 11> sliding_threshold_
				{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 };				 // arrays of values for sliding threshold for binaryzing image
			double card_aspect_ratio_;							 // Aspect Ratio of real playing cards
			int min_card_size_;									 // Min size card image in pixel²
			int max_card_size_;								 // Max size card image in pixel²
			double min_comparison_confidence_;						 // Maximum l2 error allowed for compareImages. If error is higher, card is marked as unknown			
			int perspective_transform_offset_;
			double zoom_width_ratio_;
			double zoom_height_ratio_;
			double max_rank_contour_ratio_;
			int rank_suit_zoom_offset_;		 

			void loadTrainImages(const std::string &path, std::vector<TrainImage>& train_images);			
			void identifyCard(Card& card, const cv::Mat& card_image);
			void bufferCard(const Card& card);
			bool isInArea(const Card& card, const cv::Rect& area);
			void assignCards();

		public:

			void detectCards();
			const std::vector<Card> getCards() { return this->cards_; }
			void updateFrame(const Image& input_frame);
			CardDetector(std::shared_ptr<shared::ImProcSettings>& data_gui, std::shared_ptr<shared::DataPokerDetect>& data_poker, std::shared_ptr<shared::DefaultConfig>& default_config);
			~CardDetector();

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;
					
	};

}//namespace detect
