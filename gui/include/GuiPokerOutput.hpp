#pragma once

#include <memory>

#include "ISubject.hpp"
#include "SimSettings.hpp"

namespace gui {

	class GuiPokerOutput: public interfaces::ISubject
	{
		private:

		//Camera Controls
		poker::SimSettings sim_settings_;

		public:			

            poker::SimSettings getSettings() const 
			{
				 return this->sim_settings_;
			} 
			
			void checkForUserInput(
				const bool& input_flag, 
				const poker::SimSettings sim_settings
				) 
			{
				if(input_flag)
				{  
					this->sim_settings_ = sim_settings; 
					this->notify(); 
				};
			}

        	explicit GuiPokerOutput(
				poker::SimSettings initial_settings
				): 
				sim_settings_(initial_settings) 
			{};

			virtual ~GuiPokerOutput() {};

			// Using default copy and move constructors. 
			GuiPokerOutput(const GuiPokerOutput& other) = default;	
			GuiPokerOutput& operator=(const GuiPokerOutput& other) = default;
			GuiPokerOutput(GuiPokerOutput&& other) noexcept = default;
			GuiPokerOutput& operator=(GuiPokerOutput&& other) noexcept = default;
	};

} // namespace gui

 