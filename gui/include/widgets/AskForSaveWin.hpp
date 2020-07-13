#pragma once

#include <string>

#include "IWindow.hpp"
#include "Button.hpp"

namespace gui {

	class AskForSaveWin: public IWindow
	{
		private:
		
		bool save_;
		Button button_;
        bool& show_;
		
		public:

			bool draw() override;
	
			AskForSaveWin(const std::string& name, bool& show, const int& flag = 0):
			IWindow(name, flag), save_(false),  button_(), show_(show)
			{};
			virtual ~AskForSaveWin() {};

			// Using default copy and move constructors. 
			AskForSaveWin(const AskForSaveWin& other) = default;	
			AskForSaveWin& operator=(const AskForSaveWin& other) = default;
			AskForSaveWin(AskForSaveWin&& other) noexcept = default;
			AskForSaveWin& operator=(AskForSaveWin&& other) noexcept = default;
	};

} // namespace gui

