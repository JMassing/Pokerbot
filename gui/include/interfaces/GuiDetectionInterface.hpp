#pragma once

#include <memory>

#include "IDetectGui.hpp"
#include "ImProcSettings.hpp"

namespace gui {

	/** \ingroup gui
	* @class GuiDetectionInterface
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Implements communication interface between detection and GUI module.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class GuiDetectionInterface: public detect::IDetectGui
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
			
        	GuiDetectionInterface(
				detect::ImProcSettings& settings,
				bool& input
				): 
				proc_settings_(settings),
				user_input_(input),
				cards_{} 
			{};

			virtual ~GuiDetectionInterface() {};

			// Using default copy and move constructors. 
			GuiDetectionInterface(const GuiDetectionInterface& other) = default;	
			GuiDetectionInterface& operator=(const GuiDetectionInterface& other) = default;
			GuiDetectionInterface(GuiDetectionInterface&& other) noexcept = default;
			GuiDetectionInterface& operator=(GuiDetectionInterface&& other) noexcept = default;
	};

} // namespace gui

 