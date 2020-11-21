#pragma once

#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <memory>
#include <boost/filesystem.hpp>

#include "ICardDetector.hpp"

#include "CardBuffer.hpp"
#include "ContourFinder.hpp"
#include "CardIdentifier.hpp"
#include "PerspectiveCorrector.hpp"
#include "CardAssigner.hpp"
#include "ImProcSettings.hpp"
#include "DataDetect.hpp"
#include "IDetectGui.hpp"
#include "IDetectCapture.hpp"

namespace fs = boost::filesystem;

// Detects cards in live image
namespace detect 
{
	// CompileTime constants    
	constexpr size_t CARD_BUFFER_SIZE = 30;
	// Distance used to determin which card buffer a newly detected card belongs to. In the
	// bufferCard method, the distance between the card center and all existing buffers is calculated
	// When distance is < max distance, card is added to the buffer with the smalles distance
	// when all distances > max_distance, a new buffer is created.
    constexpr double MAX_DISTANCE_TO_BUFFER = 30;

	/**
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
		  
			Image live_frame_;
			std::vector<Card> cards_;
			std::vector<CardBuffer<CARD_BUFFER_SIZE>> card_buffers_;
			int frame_nr_;
            ImProcSettings settings_;
            PerspectiveCorrector perspective_corrector_;
			const int perspective_transform_offset_ = 5;

            // Parameters used for filtering Card Contours
            const int max_card_size_ = 500000;
            const int min_card_size_ = 8000;

            // Parameters for Card Image size. Card width in pixel, apsect ratio
            // Measured from real cards used here 
            const int card_width_ = 301;
            const double card_aspect_ratio_ = 1.4;

			// Interfaces
			std::shared_ptr<IDetectGui> gui_interface_;
			std::shared_ptr<IDetectCapture> capture_interface_;

			void bufferCard(const Card& card);

		public:

			DataDetect data_;
			int game_phase_;

			void detectCards() override;
			/**
			 * @brief Updates the frame that is being processed with current live frame
			 * 
			 * @param input_frame Live frame from camera
			 * 			
			 *  */
			void updateFrame(const Image& input_frame) override;
			const std::vector<Card> getCards() override { return this->cards_; }
			/**
			 * @brief Attach communication interface to GUI
			 * 
			 * @param interface 
			 */
			void attachGuiInterface(std::shared_ptr<IDetectGui> interface)
			{
				this->gui_interface_ = interface;
			}
			/**
			 * @brief Attach communication interface to capture module
			 * 
			 * @param interface 
			 */
			void attachCaptureInterface(std::shared_ptr<IDetectCapture> interface)
			{
				this->capture_interface_ = interface;
			}

			/**
			 * @brief Construct a new Card Detector object
			 * 
			 * @param initial_settings Initial processing settings, e.g. binary thresholds etc.
			 */
			CardDetector(ImProcSettings& initial_settings):
                live_frame_{},
                cards_{},
                card_buffers_{},
                frame_nr_(0),
				data_{},
                settings_(initial_settings),
				gui_interface_(nullptr),
				capture_interface_(nullptr),
				game_phase_{0}
            {};
			~CardDetector(){};

			// Using default copy and move constructors. 
			CardDetector(const CardDetector& other) = default;	
			CardDetector& operator=(const CardDetector& other) = default;
			CardDetector(CardDetector&& other) noexcept = default;
			CardDetector& operator=(CardDetector&& other) noexcept = default;
					
	};

}//namespace detect
