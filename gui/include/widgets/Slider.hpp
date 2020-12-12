#pragma once

#include <string>
#include <imgui.h>

#include "TemplateFunctions.hpp"

namespace gui {

    /**  \ingroup gui
	 * @class Slider
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Wrapper for ImGui::Slider.
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	class Slider
	{
				
		public:
			
			/**
			 * @brief Wrapper for ImGui::SliderInt
			 * 
			 * @param name Name of slider
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
				bool changed = ImGui::SliderInt(name.c_str(), &value, min, max); 
				
				if(enforce_boundaries)
				{
					templates::enforceBoundaries(min, max, value);
				}

				return changed;
			};

			/**
			 * @brief Function overload for ImGui::SliderFloat
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
				bool changed = ImGui::SliderFloat(name.c_str(), &value, min, max); 
				
				if(enforce_boundaries)
				{
					templates::enforceBoundaries(min, max, value);
				}
				
				return changed;
			};

			Slider() {};
			virtual ~Slider() {};

			// Using default copy and move constructors. 
			Slider(const Slider& other) = default;	
			Slider& operator=(const Slider& other) = default;
			Slider(Slider&& other) noexcept = default;
			Slider& operator=(Slider&& other) noexcept = default;
	};
} // namespace gui


