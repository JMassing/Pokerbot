#pragma once

#include <string>
#include <imgui.h>

#include "TemplateFunctions.hpp"

namespace gui {

	class InputField
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
				bool changed = ImGui::InputInt(name.c_str(), &value);
								
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


