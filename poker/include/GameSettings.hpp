#pragma once

#include "DefaultConfig.hpp"

namespace poker
{
    struct GameSettings
    {
        int nr_of_human_players;
        int nr_of_simulation_runs;     
        bool start_game;
        bool stop_game;
        bool playing_game;

         void setToDefault(DefaultConfig& default_settings)
        {
            this->nr_of_simulation_runs = default_settings.nr_sim_runs;      
            this->nr_of_human_players = default_settings.nr_opponents;     
        }

        GameSettings(): 
            nr_of_human_players(1), 
            nr_of_simulation_runs(10000),
            start_game{false},
            stop_game{false},
            playing_game{false}
        {};
		~GameSettings(){};

		// Using default copy and move constructors. 
		GameSettings(const GameSettings& other) = default;	
		GameSettings& operator=(const GameSettings& other) = default;
		GameSettings(GameSettings&& other) noexcept = default;
		GameSettings& operator=(GameSettings&& other) noexcept = default;
    };
}// end namespace data