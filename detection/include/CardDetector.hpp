#pragma once

#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/dll.hpp>

#include "ICardDetector.hpp"
#include "ContourFinder.hpp"
#include "CardIdentifier.hpp"
#include "PerspectiveCorrector.hpp"
#include "CardAssigner.hpp"
#include "ImProcSettings.hpp"
#include "DataDetect.hpp"
#include "Card.hpp"
#include "Image.hpp"
#include "IDetectionDataHandler.hpp"
#include "BufferManager.hpp"

namespace fs = boost::filesystem;

namespace detect 
{
	/** *\ingroup detection
	 * @class CardDetector
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Detects Cards in the live image.
	 *		
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */

	class CardDetector: public ICardDetector
	{
		private:
			enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };
			const int perspective_transform_offset_ = 5;
			// Parameters used for filtering Card Contours
            const int max_card_size_ = 500000;
            const int min_card_size_ = 8000;
            // Parameters for Card Image size. 	
            const int card_width_ = 301; 
            const double card_aspect_ratio_ = 1.4;
		  
			Image live_frame_;
			std::vector<Card> cards_;
			int frame_nr_;
            ImProcSettings settings_;
			std::unique_ptr<IDetectionDataHandler> data_handler_;
            PerspectiveCorrector perspective_corrector_;
			BufferManager buffer_manager_;

		public:

			DataDetect data_;
			int game_phase_;

			void detectCards() override;
			/**
			 * @brief Updates the frame that is being processed with current live frame
			 *  
			 * */
			void updateFrame() override;
			const std::vector<Card> getCards() override { return this->cards_; }
			void attachDataHandler(std::unique_ptr<IDetectionDataHandler> handler)
			{
				this->data_handler_.swap(handler); 
			}
			int get_frame_nr()
			{
				return this->frame_nr_;
			}
			/**
			 * @brief Construct a new Card Detector object
			 * 
			 * @param initial_settings Initial processing settings, e.g. binary thresholds etc.
			 */
			CardDetector(ImProcSettings& initial_settings):
                live_frame_{},
                cards_{},
                buffer_manager_{},
                frame_nr_(0),
				data_{},
                settings_(initial_settings),
				game_phase_{0},
				data_handler_{nullptr}
            {};
			~CardDetector(){};

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;			
	};
}//namespace detect
