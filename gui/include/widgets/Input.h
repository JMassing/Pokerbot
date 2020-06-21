#pragma once

#include "IConstrainedInput.h"

#include <string>
#include <imgui.h>

namespace gui {

	class Input: public IConstrainedInput
	{
		protected:
				
		public:
			
			bool draw(const std::string& name, const int& min, const int& max, int& value, const bool& enforce_boundaries) override
			{
				bool changed = ImGui::InputInt(name.c_str(), &value);
				
				if(enforce_boundaries)
				{
					this->enforceBoundaries(min, max, value);
				}

				return changed;
			};
			bool draw(const std::string& name, const float& min, const float& max, float& value, const bool& enforce_boundaries) override
			{
				bool changed = ImGui::InputFloat(name.c_str(), &value);
				
				if(enforce_boundaries)
				{
					this->enforceBoundaries(min, max, value);
				}

				return changed;
			};

			Input() {};
			virtual ~Input() {};

			// Using default copy and move constructors. 
			Input(const Input& other) = default;	
			Input& operator=(const Input& other) = default;
			Input(Input&& other) noexcept = default;
			Input& operator=(Input&& other) noexcept = default;
	};
} // namespace gui


