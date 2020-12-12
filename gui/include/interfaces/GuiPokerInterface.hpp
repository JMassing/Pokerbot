#pragma once

#include <memory>

#include "IPokerGui.hpp"
#include "TemplateFunctions.hpp"
#include "Card.hpp"

namespace gui {

	/**  \ingroup gui
	 * @class GuiPokerInterface
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Implements communication interface between poker and GUI module.
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class GuiPokerInterface: public poker::IPokerGui
	{

		public:			
		
			//Poker Controls
			poker::GameSettings& game_settings_;
			bool& user_input_;
			poker::DataPoker data_;

            poker::GameSettings getSettings() const override
			{
				 return this->game_settings_;
			} 

			void setSettings( poker::GameSettings& settings) override
			{
				this->game_settings_ = settings;
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

			bool isCardMasked(bool mask_card, detect::Card card)
			{
				if( mask_card && this->data_.game_phase < poker::FLOP && 
					this->data_.game_phase > poker::NOT_STARTED )
				{
					return true;
				}
				else if( mask_card && 
                         this->data_.game_phase >= poker::FLOP && 
                         this->data_.game_phase < poker::SHOW_DOWN &&
                         templates::contains(this->data_.robot_cards.begin(), 
                                             this->data_.robot_cards.end(), card) )
				{
					return true;
				}
				else
				{
					return false;
				}
			}

        	GuiPokerInterface(
				poker::GameSettings& settings,
				bool& input
				): 
				game_settings_(settings), 
				user_input_(input),
				data_()
			{};

			virtual ~GuiPokerInterface() {};

			// Using default copy and move constructors. 
			GuiPokerInterface(const GuiPokerInterface& other) = default;	
			GuiPokerInterface& operator=(const GuiPokerInterface& other) = default;
			GuiPokerInterface(GuiPokerInterface&& other) noexcept = default;
			GuiPokerInterface& operator=(GuiPokerInterface&& other) noexcept = default;
	};

} // namespace gui

 