#pragma once

#include <string>

namespace gui {

	class Widget
	{
    
		public:
			
			virtual bool draw(bool& ) = 0;

			Widget() {};
			virtual ~Widget() {};

			// Using default copy and move constructors. 
			Widget(const Widget& other) = default;	
			Widget& operator=(const Widget& other) = default;
			Widget(Widget&& other) noexcept = default;
			Widget& operator=(Widget&& other) noexcept = default;
	};

} // namespace gui

