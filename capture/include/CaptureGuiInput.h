#pragma once

// CaptureGuiInput captures the user input for the camera settings from GUI
// and calls camera controller to update camera settings if user input occured

#include <memory>

#include "IObserver.h"
#include "GUICaptureOutput.h"
#include "CameraController.h"

namespace capture {

	class CaptureGuiInput: public interfaces::IObserver
	{ 
		private:
			
            std::shared_ptr<CameraController> camera_controller_;
			const gui::GUICaptureOutput& controls_;

		public:
			
			void update() override
            {
                this->camera_controller_->setCameraControls(controls_.getSettings());
            };
			
			CaptureGuiInput(
				const gui::GUICaptureOutput& controls, 
                std::shared_ptr<CameraController>& camera_controller
				):
				controls_(controls),
                camera_controller_(camera_controller)
			{};

			~CaptureGuiInput() {};

			// Using default copy and move constructors. 
			CaptureGuiInput(const CaptureGuiInput& other) = default;	
			CaptureGuiInput& operator=(const CaptureGuiInput& other) = default;
			CaptureGuiInput(CaptureGuiInput&& other) noexcept = default;
			CaptureGuiInput& operator=(CaptureGuiInput&& other) noexcept = default;			
	};

} //end namespace capture

