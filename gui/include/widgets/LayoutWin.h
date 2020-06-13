#pragma once

#include <memory>

#include "Window.h"
#include "LayoutWinConfig.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"

namespace gui {

	class LayoutWin: public Window
	{
		private:
		
		LayoutWinConfig config_;
		AskForSaveWin save_win_;
		bool show_ask_for_save_;
		std::shared_ptr<shared::DefaultConfig> default_config_;

		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		
		public:

			LayoutWinConfig getUserInput(){ return this->config_;};
			
			LayoutWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), 
				save_win_("##save_layout", "layout", this->show_ask_for_save_)
				{
					this->setConfigToDefault();
				};
			virtual ~LayoutWin() {};

			// Using default copy and move constructors. 
			LayoutWin(const LayoutWin& other) = default;	
			LayoutWin& operator=(const LayoutWin& other) = default;
			LayoutWin(LayoutWin&& other) noexcept = default;
			LayoutWin& operator=(LayoutWin&& other) noexcept = default;
	};

} // namespace gui

