#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "Game.h"

// Class to test methods of Game class. Make private members public to access them from TestPoker.cpp. This is only included in TestPoker.cpp 
namespace poker{
    
    class GameInternal: public Game{
       
        public:
   
        GameInternal(int nr_of_players) : Game(nr_of_players){ };
        ~GameInternal() {};
        // Using default copy and move constructors. 
        GameInternal(const GameInternal& other) = default;
        GameInternal& operator=(const GameInternal& other) = default;
        GameInternal(GameInternal&& other) noexcept = default;
        GameInternal& operator=(GameInternal&& other) noexcept = default;
    };

}//end namespace poker