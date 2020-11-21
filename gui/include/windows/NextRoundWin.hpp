#pragma once

#include <string>

#include "IWindow.hpp"
#include "InputField.hpp"
#include "Button.hpp"
#include "GuiPokerInterface.hpp"

namespace gui {

	/**
	* @class NextRoundWin
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Window that pops up when round is finished.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class NextRoundWin: public IWindow
	{
		private:
		
		InputField input_field_;
		Button button_;
		std::shared_ptr<GuiPokerInterface>& poker_if_; 


		public:
			
			void draw() override;
	
			NextRoundWin(
				const std::string& name, 
				bool& show, 
				std::shared_ptr<GuiPokerInterface>& poker_if,
				const int& flag = 0
				):
				IWindow(name, show, flag), 
				poker_if_(poker_if),
				input_field_(), 
				button_()
			{};
			virtual ~NextRoundWin() {};

			// Using default copy and move constructors. 
			NextRoundWin(const NextRoundWin& other) = default;	
			NextRoundWin& operator=(const NextRoundWin& other) = default;
			NextRoundWin(NextRoundWin&& other) noexcept = default;
			NextRoundWin& operator=(NextRoundWin&& other) noexcept = default;
	};

} // namespace gui

