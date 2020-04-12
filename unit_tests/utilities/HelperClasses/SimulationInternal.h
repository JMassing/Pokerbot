#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "Simulation.h"

// Class to test methods of Game class. Make private members public to access them from TestPoker.cpp. This is only included in TestPoker.cpp 
namespace poker{
    
    class SimulationInternal: public Simulation{
       
        public:
   
        SimulationInternal(int nr_of_players) : Simulation(nr_of_players){ };
        ~SimulationInternal() {};
        // Using default copy and move constructors. 
        SimulationInternal(const SimulationInternal& other) = default;
        SimulationInternal& operator=(const SimulationInternal& other) = default;
        SimulationInternal(SimulationInternal&& other) noexcept = default;
        SimulationInternal& operator=(SimulationInternal&& other) noexcept = default;
    };

}//end namespace poker