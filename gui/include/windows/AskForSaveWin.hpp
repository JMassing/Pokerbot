#pragma once

#include <string>

#include "IWindow.hpp"
#include "Button.hpp"

namespace gui {

	class AskForSaveWin: public IWindow
	{
		private:
		
		Button button_;
		
		public:
			bool save_;

			void draw() override;
	
			AskForSaveWin(const std::string& name, bool& show, const int& flag = 0):
			IWindow(name, show, flag), save_(false),  button_()
			{};
			virtual ~AskForSaveWin() {};

			// Using default copy and move constructors. 
			AskForSaveWin(const AskForSaveWin& other) = default;	
			AskForSaveWin& operator=(const AskForSaveWin& other) = default;
			AskForSaveWin(AskForSaveWin&& other) noexcept = default;
			AskForSaveWin& operator=(AskForSaveWin&& other) noexcept = default;
	};

} // namespace gui
