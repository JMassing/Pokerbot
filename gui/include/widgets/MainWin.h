#pragma once

#include <memory>

#include "Window.h"

namespace gui {

	class MainWin: public Window
	{
		private:
	
		virtual bool content() override;

		public:

		
			MainWin(const std::string& name, const int& flag = 0): Window(name, flag){};
			virtual ~MainWin() {};

			// Using default copy and move constructors. 
			MainWin(const MainWin& other) = default;	
			MainWin& operator=(const MainWin& other) = default;
			MainWin(MainWin&& other) noexcept = default;
			MainWin& operator=(MainWin&& other) noexcept = default;
	};

} // namespace gui

