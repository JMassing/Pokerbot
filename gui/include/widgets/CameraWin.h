#pragma once

#include <memory>

#include "Window.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "Button.h"
#include "Slider.h"
#include "CameraControls.h"

namespace gui {

	class CameraWin: public Window
	{
		private:
		
		const int max_exp_time_ = -1;
       	const int min_exp_time_ = -12;
        const int max_focus_ = 250;
        const int min_focus_ = 0;
        const int max_brightness_ = 255;
        const int min_brightness_ = 0;
		AskForSaveWin save_win_;
		bool show_ask_for_save_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		std::shared_ptr<shared::CameraControls> camera_controls_;
		Slider slider_;
		Button button_;

		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		
		
		public:
		
			CameraWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, std::shared_ptr<shared::CameraControls>& camera_controls, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), slider_{}, camera_controls_(camera_controls),
				save_win_("##save_improc", "camera settings", this->show_ask_for_save_)
				{
					this->setConfigToDefault();
				};
			virtual ~CameraWin() {};

			// Using default copy and move constructors. 
			CameraWin(const CameraWin& other) = default;	
			CameraWin& operator=(const CameraWin& other) = default;
			CameraWin(CameraWin&& other) noexcept = default;
			CameraWin& operator=(CameraWin&& other) noexcept = default;
	};

} // namespace gui

