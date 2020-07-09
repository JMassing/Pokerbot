#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include "Simulation.hpp"

// Class to test methods of Game class. Make private members public to access them from TestPoker.cpp. This is only included in TestPoker.cpp 
namespace UnitTest{
    
    class SimulationInternal: public poker::Simulation {
       
        public:
        void setRobotHand(poker::Hand hand){this->robot_hand_=hand;};
        void setPlayerHands(poker::Hand hand, int i){this->player_hands_.at(i)=hand;};
        int getWinner(){return this->determineWinner();};

        SimulationInternal(int nr_of_players, int nr_of_iterations, bool log_sim=false) : Simulation(nr_of_players, nr_of_iterations, log_sim){ };
        ~SimulationInternal() {};
        // Using default copy and move constructors. 
        SimulationInternal(const SimulationInternal& other) = default;
        SimulationInternal& operator=(const SimulationInternal& other) = default;
        SimulationInternal(SimulationInternal&& other) noexcept = default;
        SimulationInternal& operator=(SimulationInternal&& other) noexcept = default;
    };

}//end namespace UnitTest