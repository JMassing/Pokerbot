#pragma once

#include "Widget.h"

#include <string>
#include <imgui.h>

namespace gui {

	class Window: public Widget
	{
		protected:

		std::string name_;
		int flag_;
		virtual bool content() = 0;
				//// Temporary!!!!!!! Delete later
		template<class T>
        bool addButton(const char* name, T& callback);
		//		//// Temporary!!!!!!! Delete later when there is a slider class
		template<class T>
    	void enforceBoundaries(const T& min, const T& max, T& value);
		void helpMarker(const char* desc);
		
		public:
			
			virtual bool draw(bool& show) override
			{
				bool ret_val = false;
				if(show)
				{
					ImGui::Begin(this->name_.c_str(), &show, this->flag_);
					ret_val = this->content();
					ImGui::End();
				}
				return ret_val;
			};

			Window(const std::string& name, const int& flag = 0): name_(name), flag_(flag) {};
			virtual ~Window() {};

			// Using default copy and move constructors. 
			Window(const Window& other) = default;	
			Window& operator=(const Window& other) = default;
			Window(Window&& other) noexcept = default;
			Window& operator=(Window&& other) noexcept = default;
	};

		//// Temporary!!!!!!! Delete later when there is a button class

	template<class T>
    bool Window::addButton(const char* name, T& callback)
    {
        bool activated = false;
        if(ImGui::Button(name))
        {
            callback();
            activated = true;
        }                    
        return activated;       
    };		

	//		//// Temporary!!!!!!! Delete later when there is a slider class

	template<class T>
    void Window::enforceBoundaries(const T& min, const T& max, T& value)
    {
            if(value < min)
            {
                  value = min;
            }
            else if(value > max)
            {
                  value = max;
            }
            else
            {
                  //do nothing
            }            
    }

} // namespace gui

