#pragma once

#include <vector>

#include "Hand.hpp"
#include "RankDeterminator.hpp"

// Determines the winner between the given hands
namespace poker{

    class WinnerDeterminator{
        
        public:

            static int determineWinner( std::vector<Hand>& player_hands, Hand& robot_hand);

            WinnerDeterminator() {};
            ~WinnerDeterminator() {};
            
            // Using default copy and move constructors. 
            WinnerDeterminator(const WinnerDeterminator& other) = default;	
            WinnerDeterminator& operator=(const WinnerDeterminator& other) = default;
            WinnerDeterminator(WinnerDeterminator&& other) noexcept = default;
            WinnerDeterminator& operator=(WinnerDeterminator&& other) noexcept = default;

    };

}// end namespace poker