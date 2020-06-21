#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	class IConstrainedInput
	{
		protected:

		template<class T>
    	void enforceBoundaries(const T& min, const T& max, T& value);
				
		public:
			
			virtual bool draw(const std::string& name, const int& min, const int& max, int& value, const bool& enforce_boundaries) = 0;
			virtual	bool draw(const std::string& name, const float& min, const float& max, float& value, const bool& enforce_boundaries) = 0;

			IConstrainedInput() {};
			virtual ~IConstrainedInput() {};

			// Using default copy and move constructors. 
			IConstrainedInput(const IConstrainedInput& other) = default;	
			IConstrainedInput& operator=(const IConstrainedInput& other) = default;
			IConstrainedInput(IConstrainedInput&& other) noexcept = default;
			IConstrainedInput& operator=(IConstrainedInput&& other) noexcept = default;
	};

	template<class T>
    void IConstrainedInput::enforceBoundaries(const T& min, const T& max, T& value)
    {
           value < min ? value = min : value = value;
           value > max ? value = max : value = value;      
    }
} // namespace gui


