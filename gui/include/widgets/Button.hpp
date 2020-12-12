#pragma once

#include <string>
#include <imgui.h>

namespace gui {

 	/**  \ingroup gui
	 * @class Button
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Wrapper for ImGui::Button
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class Button
	{
		protected:
			
		public:
			
			/**
			 * @brief Draw Button
			 * 
			 * @tparam T 
			 * @param name Button name
			 * @param active True if button is active (i.e. can be pressed)
			 * @param callback Pointer to function that is called on button press
			 * @return true if button was pressed
			 * @return false if button was not pressed
			 */
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
					// Grey out button that is not active
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
					ImGui::Button(name.c_str());					
					ImGui::PopStyleVar();
				}
				      
				return button_pressed;
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


