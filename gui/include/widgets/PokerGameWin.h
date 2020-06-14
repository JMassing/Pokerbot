#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Window.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "PokerGameWinConfig.h"
#include "Mapping.h"
#include "Card.h"
#include "Button.h"
#include "Slider.h"
#include "Input.h"

namespace gui {

	class PokerGameWin: public Window
	{
		private:
		
		bool show_ask_for_save_;
		AskForSaveWin save_win_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		PokerGameWinConfig config_;
		detect::Mapping mapping_;
		std::pair<double,double>& probability_;
		std::vector<detect::Card>& robot_cards_;
		std::vector<detect::Card>& public_cards_;
		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();
		Slider slider_;
		Button button_;
		Input input_;
		
		public:

			PokerGameWinConfig getUserInput(){ return this->config_;};
			
			PokerGameWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, std::pair<double,double>& probability, std::vector<detect::Card>& robot_cards, std::vector<detect::Card>& public_cards, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), mapping_{}, robot_cards_(robot_cards), public_cards_(public_cards), slider_{}, button_{}, input_{},
				save_win_("##save_poker", "game settings", this->show_ask_for_save_), probability_(probability)
				{
					this->setConfigToDefault();
				};
			virtual ~PokerGameWin() {};

			// Using default copy and move constructors. 
			PokerGameWin(const PokerGameWin& other) = default;	
			PokerGameWin& operator=(const PokerGameWin& other) = default;
			PokerGameWin(PokerGameWin&& other) noexcept = default;
			PokerGameWin& operator=(PokerGameWin&& other) noexcept = default;
	};

} // namespace gui

