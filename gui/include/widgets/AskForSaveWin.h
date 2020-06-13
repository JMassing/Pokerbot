#pragma once

#include "Window.h"
#include "memory"

namespace gui {

	class AskForSaveWin: public Window
	{
		private:
		
		bool save_;
		bool& show_;
		std::string type_;

		virtual bool content() override;
		
		public:
	
			AskForSaveWin(const std::string& name, const std::string& type, bool& show, const int& flag = 0):
			Window(name, flag),	save_(false), type_(type), show_(show)
			{};
			virtual ~AskForSaveWin() {};

			// Using default copy and move constructors. 
			AskForSaveWin(const AskForSaveWin& other) = default;	
			AskForSaveWin& operator=(const AskForSaveWin& other) = default;
			AskForSaveWin(AskForSaveWin&& other) noexcept = default;
			AskForSaveWin& operator=(AskForSaveWin&& other) noexcept = default;
	};

} // namespace gui

