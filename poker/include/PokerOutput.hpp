#pragma once

// DetectOutput exposes detected cards to GUI.

#include "ISubject.hpp"
#include "DataPoker.hpp"

#include "Card.hpp"

namespace poker {

	class PokerOutput: public interfaces::ISubject
	{ 
		private:

		DataPoker& data_;

		public:
			
            DataPoker getData(){ return this->data_; };

			explicit PokerOutput(DataPoker& data): data_(data) {};

			~PokerOutput() {};

			// Using default copy and move constructors. 
			PokerOutput(const PokerOutput& other) = default;	
			PokerOutput& operator=(const PokerOutput& other) = default;
			PokerOutput(PokerOutput&& other) noexcept = default;
			PokerOutput& operator=(PokerOutput&& other) noexcept = default;			
	};

} //end namespace capture