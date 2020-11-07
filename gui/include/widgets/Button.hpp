#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	class Button
	{
		protected:
			
		public:
			
			template<class T>
			bool draw(const std::string name, const bool& active, const T& callback)
			{
				bool button_pressed = false;
				if(active)
				{
					if(ImGui::Button(name.c_str()))
					{
						callback();
						button_pressed = true;
					} 
				}
				else
				{
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
					ImGui::Button(name.c_str());					
					ImGui::PopStyleVar();
				}
				      
				return button_pressed ;
			};

			Button() {};
			~Button() {};

			// Using default copy and move constructors. 
			Button(const Button& other) = default;	
			Button& operator=(const Button& other) = default;
			Button(Button&& other) noexcept = default;
			Button& operator=(Button&& other) noexcept = default;
	};
} // namespace gui


