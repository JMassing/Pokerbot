#pragma once

// Observes CaptureOutput and gets live frame

#include <memory>

#include "GuiDetectionOutput.hpp"
#include "IObserver.hpp"
#include "ImProcSettings.hpp"

namespace detect {

	class DetectGuiInput: public interfaces::IObserver
	{ 
		public:

			const gui::GuiDetectionOutput& controls_;
			ImProcSettings im_proc_settings_;

			
			void update() override
            {
                this->im_proc_settings_ = this->controls_.getSettings();
            };
			
			DetectGuiInput(
				const gui::GuiDetectionOutput& controls,
				const ImProcSettings& initial_settings
				):
				controls_(controls),
				im_proc_settings_{initial_settings}
			{};

			~DetectGuiInput() {};

			// Using default copy and move constructors. 
			DetectGuiInput(const DetectGuiInput& other) = default;	
			DetectGuiInput& operator=(const DetectGuiInput& other) = default;
			DetectGuiInput(DetectGuiInput&& other) noexcept = default;
			DetectGuiInput& operator=(DetectGuiInput&& other) noexcept = default;			
	};

} //end namespace detect