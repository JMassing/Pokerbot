#pragma once

#include <memory>

#include "IPokerGui.hpp"

namespace gui {

	class GuiPokerInterface: public poker::IPokerGui
	{

		public:			
		
			//Poker Controls
			poker::GameSettings& game_settings_;
			bool& user_input_;
			poker::DataPoker data_;
			int bet_size_;
			bool bet_placed_;

            poker::GameSettings getSettings() const override
			{
				 return this->game_settings_;
			} 
			
			bool checkUserInput() const override
			{
				return this->user_input_;
			}

			void setData(const poker::DataPoker& data) override
			{
				this->data_ = data;
			}

			poker::DataPoker getData() override
			{
				return this->data_;
			}

			int getBetSize() override
			{
				if(this->bet_placed_)
				{
					this->bet_placed_ = false;
					return this->bet_size_;
				}
				else
				{
					return 0;
				}

			}

        	GuiPokerInterface(
				poker::GameSettings& settings,
				bool& input
				): 
				game_settings_(settings), 
				user_input_(input),
				data_(),
				bet_size_(0),
				bet_placed_{false}
			{};

			virtual ~GuiPokerInterface() {};

			// Using default copy and move constructors. 
			GuiPokerInterface(const GuiPokerInterface& other) = default;	
			GuiPokerInterface& operator=(const GuiPokerInterface& other) = default;
			GuiPokerInterface(GuiPokerInterface&& other) noexcept = default;
			GuiPokerInterface& operator=(GuiPokerInterface&& other) noexcept = default;
	};

} // namespace gui

 