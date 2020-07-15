#pragma once

#include <memory>

#include "DataPoker.hpp"
#include "SimSettings.hpp"
#include "IPokerGui.hpp"

namespace gui {

	class GuiPokerInterface: public poker::IPokerGui
	{

		public:			
		
			//Camera Controls
			poker::SimSettings& sim_settings_;
			bool& user_input_;
			poker::DataPoker data_;

            poker::SimSettings getSettings() const override
			{
				 return this->sim_settings_;
			} 
			
			bool checkUserInput() const override
			{
				return this->user_input_;
			}

			void setData(const poker::DataPoker& data) override
			{
				this->data_ = data;
			}

        	GuiPokerInterface(
				poker::SimSettings& settings,
				bool& input
				): 
				sim_settings_(settings), 
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

 