#pragma once

#include <memory>

#include "Window.h"
#include "LayoutConfig.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "Button.h"
#include "Slider.h"

namespace gui {

	class LayoutWin: public Window
	{
		private:
		
		std::shared_ptr<LayoutConfig> config_;
		AskForSaveWin save_win_;
		bool show_ask_for_save_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		Slider slider_;
		Button button_;
		const int card_image_height_ = 150;
        const int card_rank_suit_height_ = 50;
		const int min_card_image_height_percent_ = 25; 
		const int max_card_image_height_percent_ = 175; 
		const int min_rank_suit_image_height_percent_ = 25; 
		const int max_rank_suit_image_height_percent_ = 175; 


		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		
		public:
		
			LayoutWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, std::shared_ptr<LayoutConfig>& config, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), config_(config),
				save_win_("##save_layout", "layout", this->show_ask_for_save_), slider_{}, button_{}
				{};
			virtual ~LayoutWin() {};

			// Using default copy and move constructors. 
			LayoutWin(const LayoutWin& other) = default;	
			LayoutWin& operator=(const LayoutWin& other) = default;
			LayoutWin(LayoutWin&& other) noexcept = default;
			LayoutWin& operator=(LayoutWin&& other) noexcept = default;
	};

} // namespace gui

