#pragma once

#include <memory>

#include "IDetectGui.hpp"
#include "ImProcSettings.hpp"

namespace gui {

	class GuiDetectionIO: public detect::IDetectGui
	{
		public:

			//Camera Controls
			std::vector<detect::Card> cards_;
			detect::ImProcSettings& proc_settings_;
			bool& user_input_;			

            detect::ImProcSettings getSettings() const override 
			{
				 return this->proc_settings_;
			} 

			bool checkUserInput() const override
			{
				return this->user_input_;
			}

			void setCards(std::vector<detect::Card> cards) override
			{
				this->cards_ = cards;
			}
			
        	GuiDetectionIO(
				detect::ImProcSettings& settings,
				bool& input
				): 
				proc_settings_(settings),
				user_input_(input),
				cards_{} 
			{};

			virtual ~GuiDetectionIO() {};

			// Using default copy and move constructors. 
			GuiDetectionIO(const GuiDetectionIO& other) = default;	
			GuiDetectionIO& operator=(const GuiDetectionIO& other) = default;
			GuiDetectionIO(GuiDetectionIO&& other) noexcept = default;
			GuiDetectionIO& operator=(GuiDetectionIO&& other) noexcept = default;
	};

} // namespace gui

 