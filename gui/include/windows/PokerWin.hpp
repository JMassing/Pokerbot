#pragma once

#include <memory>

#include "IWindow.hpp"
#include "Mapping.hpp"
#include "LayoutConfig.hpp"
#include "GuiPokerInterface.hpp"
#include "PlaceBetWin.hpp"
#include "WhoWonWin.hpp"
#include "NextRoundWin.hpp"

namespace gui {
	/**
	* @class PokerWin
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Window showing information concerning the poker game.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class PokerWin: public IWindow
	{
		private:
		
		Mapping mapping_;
		LayoutConfig& layout_settings_;
		std::shared_ptr<GuiPokerInterface>& poker_if_;
		PlaceBetWin place_bet_win_;
		WhoWonWin who_won_win_;
		NextRoundWin next_round_win_;
		bool show_place_bet_win_;
		bool show_who_won_win_;
		bool show_next_round_win_;
		
		public:

			void draw() override;

			PokerWin(
                const std::string& name,
				bool& show,
				LayoutConfig& layout_settings,
				std::shared_ptr<GuiPokerInterface>& poker_if,
                const int& flag = 0
                ):
				IWindow(name, show, flag), 
                mapping_{},
				layout_settings_{layout_settings},
				poker_if_(poker_if),	
				show_place_bet_win_(false),
				show_who_won_win_(false),
				show_next_round_win_(false),
				place_bet_win_("", this->show_place_bet_win_, poker_if, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize),
				who_won_win_("", this->show_who_won_win_, poker_if, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize),			
				next_round_win_("", this->show_next_round_win_, poker_if, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize)			
			{};

			virtual ~PokerWin() {};

			// Using default copy and move constructors. 
			PokerWin(const PokerWin& other) = default;	
			PokerWin& operator=(const PokerWin& other) = default;
			PokerWin(PokerWin&& other) noexcept = default;
			PokerWin& operator=(PokerWin&& other) noexcept = default;
	};

} // namespace gui