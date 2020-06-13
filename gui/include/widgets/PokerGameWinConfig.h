#pragma once

#include <opencv2/core.hpp>

namespace gui {

    struct PokerGameWinConfig
    {
        int max_sim_runs;
        int min_sim_runs;
        int nr_sim_runs;
        int min_players;
        int max_players;
        int nr_of_players;

        PokerGameWinConfig(): 
        max_sim_runs(100000), min_sim_runs(0), nr_sim_runs(10000), min_players{1}, max_players{9}, nr_of_players{1}            
        {};
        ~PokerGameWinConfig(){};

        // Using default copy and move constructors. 
        PokerGameWinConfig(const PokerGameWinConfig& other) = default;	
        PokerGameWinConfig& operator=(const PokerGameWinConfig& other) = default;
        PokerGameWinConfig(PokerGameWinConfig&& other) noexcept = default;
        PokerGameWinConfig& operator=(PokerGameWinConfig&& other) noexcept = default;
    };
}//end namespace gui