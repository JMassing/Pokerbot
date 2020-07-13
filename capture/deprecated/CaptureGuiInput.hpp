#pragma once

// CaptureGuiInput captures the user input for the camera settings from GUI
// and calls camera controller to update camera settings if user input occured

#include <memory>

#include "IObserver.hpp"
#include "GuiCaptureOutput.hpp"
#include "ICameraDevice.hpp"

namespace capture {

	class CaptureGuiInput: public interfaces::IObserver
	{ 
		private:
			
            std::shared_ptr<ICameraDevice> camera_controller_;
			const gui::GuiCaptureOutput& controls_;

		public:
			
			void update() override
            {
                this->camera_controller_->setCameraControls(controls_.getSettings());
            };

			void connectCameraDevice(std::shared_ptr<ICameraDevice> camera_controller)
			{
				this->camera_controller_ = camera_controller;
			};
			
			CaptureGuiInput(
				const gui::GuiCaptureOutput& controls 
				):
				controls_(controls),
                camera_controller_{}
			{};

			~CaptureGuiInput() {};

			// Using default copy and move constructors. 
			CaptureGuiInput(const CaptureGuiInput& other) = default;	
			CaptureGuiInput& operator=(const CaptureGuiInput& other) = default;
			CaptureGuiInput(CaptureGuiInput&& other) noexcept = default;
			CaptureGuiInput& operator=(CaptureGuiInput&& other) noexcept = default;			
	};

} //end namespace capture

