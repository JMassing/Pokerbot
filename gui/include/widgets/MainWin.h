#pragma once

#include "Window.h"
#include "Button.h"

namespace gui {

	class MainWin: public Window
	{
		private:
		Button button_;
	
		virtual bool content() override;

		public:

		
			MainWin(const std::string& name, const int& flag = 0): Window(name, flag), button_{} {};
			virtual ~MainWin() {};

			// Using default copy and move constructors. 
			MainWin(const MainWin& other) = default;	
			MainWin& operator=(const MainWin& other) = default;
			MainWin(MainWin&& other) noexcept = default;
			MainWin& operator=(MainWin&& other) noexcept = default;
	};

} // namespace gui

