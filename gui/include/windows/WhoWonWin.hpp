#pragma once

#include <string>

#include "IWindow.hpp"
#include "InputField.hpp"
#include "Button.hpp"
#include "GuiPokerInterface.hpp"

namespace gui {
	/**  \ingroup gui
	 * @class WhoWonWin
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Window asking player to enter who won the round.
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class WhoWonWin: public IWindow
	{
		private:
		
		InputField input_field_;
		Button button_;
		std::shared_ptr<GuiPokerInterface>& poker_if_; 
		int winner_;

		public:
			
			void draw() override;
	
			WhoWonWin(
				const std::string& name, 
				bool& show, 
				std::shared_ptr<GuiPokerInterface>& poker_if,
				const int& flag = 0
				):
				IWindow(name, show, flag), 
				poker_if_(poker_if),
				input_field_(), 
				button_(),
				winner_(-1)
			{};
			virtual ~WhoWonWin() {};

			// Using default copy and move constructors. 
			WhoWonWin(const WhoWonWin& other) = default;	
			WhoWonWin& operator=(const WhoWonWin& other) = default;
			WhoWonWin(WhoWonWin&& other) noexcept = default;
			WhoWonWin& operator=(WhoWonWin&& other) noexcept = default;
	};

} // namespace gui

