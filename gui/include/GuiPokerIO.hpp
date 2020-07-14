#pragma once

#include <memory>

#include "DataPoker.hpp"
#include "SimSettings.hpp"
#include "IPokerGui.hpp"

namespace gui {

	class GuiPokerIO: public poker::IPokerGui
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

        	GuiPokerIO(
				poker::SimSettings& settings,
				bool& input
				): 
				sim_settings_(settings), 
				user_input_(input),
				data_()
			{};

			virtual ~GuiPokerIO() {};

			// Using default copy and move constructors. 
			GuiPokerIO(const GuiPokerIO& other) = default;	
			GuiPokerIO& operator=(const GuiPokerIO& other) = default;
			GuiPokerIO(GuiPokerIO&& other) noexcept = default;
			GuiPokerIO& operator=(GuiPokerIO&& other) noexcept = default;
	};

} // namespace gui

 