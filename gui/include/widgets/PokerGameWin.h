#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Window.h"
#include "DefaultConfig.h"
#include "AskForSaveWin.h"
#include "Mapping.h"
#include "Card.h"
#include "Button.h"
#include "Slider.h"
#include "Input.h"
#include "DataDetectGui.h"
#include "DataPokerGui.h"

namespace gui {

	class PokerGameWin: public Window
	{
		private:
		
		const int min_players_ = 1;
        const int max_players_ = 9;
		const int max_sim_runs_ = 100000;
        const int min_sim_runs_ = 0;
		bool show_ask_for_save_;
		AskForSaveWin save_win_;
		std::shared_ptr<shared::DefaultConfig> default_config_;
		detect::Mapping mapping_;
		std::shared_ptr<shared::DataDetectGui> data_detect_;
        std::shared_ptr<shared::DataPokerGui> data_poker_;
		Slider slider_;
		Button button_;
		Input input_;	
		std::vector<detect::Card> robot_cards_;
		std::vector<detect::Card> public_cards_;


		virtual bool content() override;
		void setConfigToDefault();
		void saveConfigAsDefault();

		
		public:
	
			PokerGameWin(const std::string& name, std::shared_ptr<shared::DefaultConfig>& default_config, std::shared_ptr<shared::DataPokerGui>& data_poker, std::vector<detect::Card> robot_cards,
			 std::vector<detect::Card> public_cards, const int& flag = 0):
				Window(name, flag), default_config_(default_config), show_ask_for_save_(false), mapping_{}, slider_{}, button_{}, input_{}, data_poker_(data_poker), robot_cards_(robot_cards), public_cards_(public_cards),
				save_win_("##save_poker", "game settings", this->show_ask_for_save_)
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

