#pragma once

#include <memory>

#include "Window.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "Button.h"
#include "Slider.h"
#include "DataDetectGui.h"

namespace gui {

	class ImProcWin: public Window
	{
		private:
		
		AskForSaveWin save_win_;
		bool show_ask_for_save_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		std::shared_ptr<shared::DataDetectGui> data_detect_;
		Button button_;
		Slider slider_;
		const int max_live_th_ = 255;
        const int min_live_th_ = 0;
        const int max_bin_th_ = 255;
        const int min_bin_th_ = 0;
        const int max_ident_th_ = 255;
        const int min_ident_th_ = 0;


		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		
		public:
	
			ImProcWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, std::shared_ptr<shared::DataDetectGui>& data_detect, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), button_{}, slider_{}, data_detect_(data_detect),
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

