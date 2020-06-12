#pragma once

#include <string>

namespace gui {

	class Widget
	{
        protected:

            std::string name;

		public:
			
			virtual void draw() = 0;

			Widget() {};
			virtual ~Widget() {};

			// Using default copy and move constructors. 
			Widget(const Widget& other) = default;	
			Widget& operator=(const Widget& other) = default;
			Widget(Widget&& other) noexcept = default;
			Widget& operator=(Widget&& other) noexcept = default;
	};

} // namespace gui

