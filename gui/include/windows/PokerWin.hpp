#pragma once

#include "IWindow.hpp"
#include "Mapping.hpp"
#include "DataPoker.hpp"
#include "LayoutConfig.hpp"

namespace gui {

	class PokerWin: public IWindow
	{
		private:
		
		Mapping mapping_;
		poker::DataPoker& data_;
		LayoutConfig& layout_settings_;
		
		public:

			void draw() override;

			PokerWin(
                const std::string& name,
				bool& show,
                poker::DataPoker& data,
				LayoutConfig& layout_settings,
                const int& flag = 0
                ):
				IWindow(name, show, flag), 
                data_(data),
                mapping_{},
				layout_settings_{layout_settings}
			{};

			virtual ~PokerWin() {};

			// Using default copy and move constructors. 
			PokerWin(const PokerWin& other) = default;	
			PokerWin& operator=(const PokerWin& other) = default;
			PokerWin(PokerWin&& other) noexcept = default;
			PokerWin& operator=(PokerWin&& other) noexcept = default;
	};

} // namespace gui