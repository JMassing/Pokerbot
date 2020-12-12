#pragma once

#include <string>
#include <imgui.h>

#include "TemplateFunctions.hpp"

namespace gui {

 	/**  \ingroup gui
	 * @class InputField
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Wrapper for ImGui::Input
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class InputField
	{				
		public:
			
			/**
			 * @brief Wrapper for ImGui::InputInt
			 * 
			 * @param name Name of input field
			 * @param min min value
			 * @param max max value
			 * @param value default
			 * @param enforce_boundaries true to enforce min <= value <= max
			 * @return true if user input
			 * @return false if no user input
			 */
			bool draw(
				const std::string& name, 
				const int& min,
				const int& max, 
				int& value, 
				const bool& enforce_boundaries
				)
			{
				bool changed = ImGui::InputInt(name.c_str(), &value);
								
				if(enforce_boundaries)
				{ 
					templates::enforceBoundaries(min, max, value);
				} 

				return changed;
			};
			
			/**
			 * @brief Function overload for ImGui::InputFloat
			 * 
			 */
			bool draw(
				const std::string& name, 
				const float& min, 
				const float& max,
				float& value, 
				const bool& enforce_boundaries
				)
			{
				bool changed = ImGui::InputFloat(name.c_str(), &value);
				
				if(enforce_boundaries)
				{ 
					templates::enforceBoundaries(min, max, value);
				} 
				return changed;
			};

			InputField() {};
			virtual ~InputField() {};

			// Using default copy and move constructors. 
			InputField(const InputField& other) = default;	
			InputField& operator=(const InputField& other) = default;
			InputField(InputField&& other) noexcept = default;
			InputField& operator=(InputField&& other) noexcept = default;
	};
} // namespace gui


