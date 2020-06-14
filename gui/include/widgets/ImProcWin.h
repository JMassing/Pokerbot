#pragma once

#include <memory>

#include "Window.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "ImProcWinConfig.h"
#include "Button.h"
#include "Slider.h"

namespace gui {

	class ImProcWin: public Window
	{
		private:
		
		AskForSaveWin save_win_;
		bool show_ask_for_save_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		ImProcWinConfig config_;
		Button button_;
		Slider slider_;

		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		
		public:

			ImProcWinConfig getUserInput(){ return this->config_;};
			
			ImProcWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), button_{}, slider_{},
				save_win_("##save_improc", "image processing settings", this->show_ask_for_save_)
				{
					this->setConfigToDefault();
				};
			virtual ~ImProcWin() {};

			// Using default copy and move constructors. 
			ImProcWin(const ImProcWin& other) = default;	
			ImProcWin& operator=(const ImProcWin& other) = default;
			ImProcWin(ImProcWin&& other) noexcept = default;
			ImProcWin& operator=(ImProcWin&& other) noexcept = default;
	};

} // namespace gui

