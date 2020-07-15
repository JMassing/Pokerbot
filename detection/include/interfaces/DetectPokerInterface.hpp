#pragma once

// DetectOutput exposes detected cards to GUI.

#include "IPokerDetect.hpp"
#include "DataDetect.hpp"

namespace detect {

	class DetectPokerInterface: public poker::IPokerDetect
	{ 
		private:

		DataDetect& data_;

		public:
			
            DataDetect getData() const override { return this->data_; };

			explicit DetectPokerInterface(DataDetect& data): data_(data) {};

			~DetectPokerInterface() {};

			// Using default copy and move constructors. 
			DetectPokerInterface(const DetectPokerInterface& other) = default;	
			DetectPokerInterface& operator=(const DetectPokerInterface& other) = default;
			DetectPokerInterface(DetectPokerInterface&& other) noexcept = default;
			DetectPokerInterface& operator=(DetectPokerInterface&& other) noexcept = default;			
	};

} //end namespace capture