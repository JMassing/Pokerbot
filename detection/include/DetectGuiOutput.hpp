#pragma once

// DetectOutput exposes detected cards to GUI.

#include "ISubject.hpp"
#include "ICardDetector.hpp"

#include "Card.hpp"

namespace detect {

	class DetectGuiOutput: public interfaces::ISubject
	{ 
		private:

		std::shared_ptr<ICardDetector> detector_;

		public:
			
            std::vector<Card> getCards(){return this->detector_->getCards();};

            void connectCardDetector(std::shared_ptr<ICardDetector> detector)
			{
				this->detector_ = detector;
			}

			explicit DetectGuiOutput(){};

			~DetectGuiOutput() {};

			// Using default copy and move constructors. 
			DetectGuiOutput(const DetectGuiOutput& other) = default;	
			DetectGuiOutput& operator=(const DetectGuiOutput& other) = default;
			DetectGuiOutput(DetectGuiOutput&& other) noexcept = default;
			DetectGuiOutput& operator=(DetectGuiOutput&& other) noexcept = default;			
	};

} //end namespace capture