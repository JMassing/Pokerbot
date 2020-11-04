#pragma once

#include <string>
#include <imgui.h>

#include "TemplateFunctions.hpp"

namespace gui {

	class Slider
	{
				
		public:
			
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


