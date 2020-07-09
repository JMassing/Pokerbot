#pragma once

// DetectOutput exposes detected cards to GUI.

#include "ISubject.hpp"
#include "DataDetect.hpp"

#include "Card.hpp"

namespace detect {

	class DetectPokerOutput: public interfaces::ISubject
	{ 
		private:

		DataDetect& data_;

		public:
			
            DataDetect getData(){ return this->data_; };

			explicit DetectPokerOutput(DataDetect& data): data_(data) {};

			~DetectPokerOutput() {};

			// Using default copy and move constructors. 
			DetectPokerOutput(const DetectPokerOutput& other) = default;	
			DetectPokerOutput& operator=(const DetectPokerOutput& other) = default;
			DetectPokerOutput(DetectPokerOutput&& other) noexcept = default;
			DetectPokerOutput& operator=(DetectPokerOutput&& other) noexcept = default;			
	};

} //end namespace capture