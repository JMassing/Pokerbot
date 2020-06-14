#pragma once

#include <memory>

#include "Window.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "CameraWinConfig.h"
#include "Button.h"
#include "Slider.h"

namespace gui {

	class CameraWin: public Window
	{
		private:
		
		AskForSaveWin save_win_;
		bool show_ask_for_save_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		CameraWinConfig config_;
		Slider slider_;
		Button button_;

		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		
		
		public:

			CameraWinConfig getUserInput(){ return this->config_;};
			
			CameraWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), slider_{},
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

