#pragma once

#include <vector>

#include "Hand.hpp"
#include "RankDeterminator.hpp"

namespace poker{

    /**  \ingroup poker
	 * @class RankDeterminator
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Determines the winner between the given hands       
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
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