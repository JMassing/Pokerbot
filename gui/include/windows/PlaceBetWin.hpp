#pragma once

#include <string>

#include "IWindow.hpp"
#include "InputField.hpp"
#include "Button.hpp"
#include "GuiPokerInterface.hpp"

namespace gui {

	/**  \ingroup gui
	 * @class PlaceBetWin
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Window that pops up when it is the players turn to place his bet.
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class PlaceBetWin: public IWindow
	{
		private:
		
		InputField input_field_;
		Button button_;
		std::shared_ptr<GuiPokerInterface>& poker_if_; 
		int bet_size_;

		public:
			
			void draw() override;
	
			PlaceBetWin(
				const std::string& name, 
				bool& show, 
				std::shared_ptr<GuiPokerInterface>& poker_if,
				const int& flag = 0
				):
				IWindow(name, show, flag), 
				poker_if_(poker_if),
				input_field_(), 
				button_(),
				bet_size_(0)
			{};
			virtual ~PlaceBetWin() {};

			// Using default copy and move constructors. 
			PlaceBetWin(const PlaceBetWin& other) = default;	
			PlaceBetWin& operator=(const PlaceBetWin& other) = default;
			PlaceBetWin(PlaceBetWin&& other) noexcept = default;
			PlaceBetWin& operator=(PlaceBetWin&& other) noexcept = default;
	};

} // namespace gui

