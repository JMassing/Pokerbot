#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	class Window
	{
		protected:

		std::string name_;
		int flag_;
		virtual bool content() = 0;
		void helpMarker(const char* desc);
		
		public:
			
			bool draw(bool& show)
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

} // namespace gui

