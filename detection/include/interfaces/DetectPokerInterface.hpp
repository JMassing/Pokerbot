#pragma once

// DetectOutput exposes detected cards to GUI.

#include "IPokerDetect.hpp"
#include "DataDetect.hpp"

namespace detect {

	class DetectPokerInterface: public poker::IPokerDetect
	{ 
		private:

		DataDetect& data_;
		int& game_phase_;

		public:
			
            DataDetect getData() const override { return this->data_; };
			void setGamePhase(int game_phase) override { this->game_phase_ = game_phase; };

			explicit DetectPokerInterface(DataDetect& data, int& game_phase): 
				data_(data),
				game_phase_(game_phase)
			{};

			~DetectPokerInterface() {};

			// Using default copy and move constructors. 
			DetectPokerInterface(const DetectPokerInterface& other) = default;	
			DetectPokerInterface& operator=(const DetectPokerInterface& other) = default;
			DetectPokerInterface(DetectPokerInterface&& other) noexcept = default;
			DetectPokerInterface& operator=(DetectPokerInterface&& other) noexcept = default;			
	};

} //end namespace capture