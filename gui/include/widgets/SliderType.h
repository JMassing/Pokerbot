#pragma once

#include <string>
#include <imgui.h>

namespace gui {

	class SliderType
	{
		protected:

		template<class T>
    	void enforceBoundaries(const T& min, const T& max, T& value);
				
		public:
			
			virtual bool draw(const std::string name, const int min, const int max, int& value, bool enforce_boundaries) = 0;
			virtual	bool draw(const std::string name, const float min, const float max, float& value, bool enforce_boundaries) = 0;

			SliderType() {};
			virtual ~SliderType() {};

			// Using default copy and move constructors. 
			SliderType(const SliderType& other) = default;	
			SliderType& operator=(const SliderType& other) = default;
			SliderType(SliderType&& other) noexcept = default;
			SliderType& operator=(SliderType&& other) noexcept = default;
	};

	template<class T>
    void SliderType::enforceBoundaries(const T& min, const T& max, T& value)
    {
           value < min ? value = min : value = value;
           value > max ? value = max : value = value;      
    }
} // namespace gui


