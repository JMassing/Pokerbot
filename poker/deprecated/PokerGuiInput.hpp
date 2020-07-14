#pragma once

// Observes CaptureOutput and gets live frame

#include "GuiPokerOutput.hpp"
#include "IObserver.hpp"
#include "SimSettings.hpp"

namespace poker {

	class PokerGuiInput: public interfaces::IObserver
	{ 
		public:

			const gui::GuiPokerOutput& controls_;
			SimSettings sim_settings_;

			
			void update() override
            {
                this->sim_settings_ = this->controls_.getSettings();
            };
			
			PokerGuiInput(
				const gui::GuiPokerOutput& controls,
				const SimSettings& initial_settings
				):
				controls_(controls),
				sim_settings_{initial_settings}
			{};

			~PokerGuiInput() {};

			// Using default copy and move constructors. 
			PokerGuiInput(const PokerGuiInput& other) = default;	
			PokerGuiInput& operator=(const PokerGuiInput& other) = default;
			PokerGuiInput(PokerGuiInput&& other) noexcept = default;
			PokerGuiInput& operator=(PokerGuiInput&& other) noexcept = default;			
	};

} //end namespace detect