#pragma once

#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <memory>

#include "ICardDetector.hpp"

#include "CardBuffer.hpp"
#include "ContourFinder.hpp"
#include "CardIdentifier.hpp"
#include "PerspectiveCorrector.hpp"
#include "CardAssigner.hpp"
#include "ImProcSettings.hpp"
#include "DataDetect.hpp"

namespace detect 
{
	 // CompileTime constants    
	constexpr size_t CARD_BUFFER_SIZE = 10;
    constexpr double MAX_DISTANCE_TO_BUFFER = 200;

	class CardDetector: public ICardDetector
	{

		private:
			enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };
		  
			capture::Image live_frame_;
			std::vector<Card> cards_;
			std::vector<CardBuffer<CARD_BUFFER_SIZE>> card_buffers_;
			int frame_nr_;
            ImProcSettings& settings_;
            PerspectiveCorrector perspective_corrector_;

			const int perspective_transform_offset_ = 5;

            // Parameters used for filtering Card Contours
            const int max_card_size_ = 500000;
            const int min_card_size_ = 8000;

            // Parameters for Card Image size. Card width in pixel, apsect ratio
            // Measured from real cards used here 
            const int card_width_ = 301;
            const double card_aspect_ratio_ = 1.4;

    		void bufferCard(const Card& card);

		public:

			DataDetect data_;

			void detectCards() override;
			const std::vector<Card> getCards() override { return this->cards_; }
			void updateFrame(const capture::Image& input_frame) override;

			CardDetector(ImProcSettings& settings):
                live_frame_{},
                cards_{},
                card_buffers_{},
                frame_nr_(0),
				data_{},
                settings_(settings)
            {};
			~CardDetector(){};

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;
					
	};

}//namespace detect
