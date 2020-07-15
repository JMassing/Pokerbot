#pragma once

#include "IWindow.hpp"
#include "Mapping.hpp"
#include "DataPoker.hpp"

namespace gui {

	class PokerWin: public IWindow
	{
		private:
		
		Mapping mapping_;
		poker::DataPoker& data_;
		
		public:

			void draw() override;

			PokerWin(
                const std::string& name,
				bool& show,
                poker::DataPoker& data,
                const int& flag = 0
                ):
				IWindow(name, show, flag), 
                data_(data),
                mapping_{}
			{};

			virtual ~PokerWin() {};

			// Using default copy and move constructors. 
			PokerWin(const PokerWin& other) = default;	
			PokerWin& operator=(const PokerWin& other) = default;
			PokerWin(PokerWin&& other) noexcept = default;
			PokerWin& operator=(PokerWin&& other) noexcept = default;
	};

} // namespace gui