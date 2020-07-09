#pragma once

// Observes CaptureOutput and gets live frame

#include <memory>

#include "DetectPokerOutput.hpp"
#include "DataDetect.hpp"
#include "IObserver.hpp"

namespace poker {

	class PokerDetectInput: public interfaces::IObserver
	{ 
		private:
			
			detect::DetectPokerOutput& detect_out_;

		public:
			
			detect::DataDetect data_;

			void update() override
            {                
				this->data_ = this->detect_out_.getData();
            };
			
			PokerDetectInput(detect::DetectPokerOutput& detect_out):
				detect_out_(detect_out),
				data_{}
			{};

			~PokerDetectInput() {};

			// Using default copy and move constructors. 
			PokerDetectInput(const PokerDetectInput& other) = default;	
			PokerDetectInput& operator=(const PokerDetectInput& other) = default;
			PokerDetectInput(PokerDetectInput&& other) noexcept = default;
			PokerDetectInput& operator=(PokerDetectInput&& other) noexcept = default;			
	};

} //end namespace detect