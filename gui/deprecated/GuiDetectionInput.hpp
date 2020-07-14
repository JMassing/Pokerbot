#pragma once

// Attaches to DetectGuiOutput interface and gets cards for displaying of card images
// Contours and Rank/Suit Images

#include <memory>
#include <vector>

#include "IObserver.hpp"
#include "DetectGuiOutput.hpp"
#include "Card.hpp"

namespace gui {

	class GuiDetectionInput: public interfaces::IObserver
	{ 
		public:

			std::vector<detect::Card> cards_;
			detect::DetectGuiOutput& detect_out_;
			
			void update() override
            {
                this->cards_ = this->detect_out_.getCards();
            };
			
			GuiDetectionInput(detect::DetectGuiOutput& detect_out):
				detect_out_(detect_out),
				cards_{}
			{};

			~GuiDetectionInput() {};

			// Using default copy and move constructors. 
			GuiDetectionInput(const GuiDetectionInput& other) = default;	
			GuiDetectionInput& operator=(const GuiDetectionInput& other) = default;
			GuiDetectionInput(GuiDetectionInput&& other) noexcept = default;
			GuiDetectionInput& operator=(GuiDetectionInput&& other) noexcept = default;			
	};

}

