#pragma once

// Attaches to DetectGuiOutput interface and gets cards for displaying of card images
// Contours and Rank/Suit Images

#include <memory>
#include <vector>

#include "IObserver.hpp"
#include "PokerOutput.hpp"
#include "DataPoker.hpp"

namespace gui {

	class GuiPokerInput: public interfaces::IObserver
	{ 
		public:

			poker::DataPoker data_;
			poker::PokerOutput& poker_out_;
			
			void update() override
            {
                this->data_ = this->poker_out_.getData();
            };
			
			GuiPokerInput(poker::PokerOutput& poker_out):
				poker_out_(poker_out),
				data_{}
			{};

			~GuiPokerInput() {};

			// Using default copy and move constructors. 
			GuiPokerInput(const GuiPokerInput& other) = default;	
			GuiPokerInput& operator=(const GuiPokerInput& other) = default;
			GuiPokerInput(GuiPokerInput&& other) noexcept = default;
			GuiPokerInput& operator=(GuiPokerInput&& other) noexcept = default;			
	};

}

