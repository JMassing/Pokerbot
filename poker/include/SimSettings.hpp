#pragma once

// Data Structure holding input data from gui

#include "DefaultConfig.hpp"

namespace poker
{
    struct SimSettings
    {
        int nr_of_human_players;
        int nr_of_simulation_runs;     

         void setToDefault(shared::DefaultConfig& default_settings)
        {
            this->nr_of_simulation_runs = default_settings.nr_sim_runs;      
            this->nr_of_human_players = default_settings.nr_opponents;     
        }

        SimSettings(): 
            nr_of_human_players(1), 
            nr_of_simulation_runs(10000)
        {};
		~SimSettings(){};

		// Using default copy and move constructors. 
		SimSettings(const SimSettings& other) = default;	
		SimSettings& operator=(const SimSettings& other) = default;
		SimSettings(SimSettings&& other) noexcept = default;
		SimSettings& operator=(SimSettings&& other) noexcept = default;
    };
}// end namespace data