#pragma once

#include <utility>


#include <opencv2/core.hpp>


namespace data
{
    struct DataPokerGui
    {
        int nr_of_human_players;
        std::pair<double,double> probability;
        int nr_of_simulation_runs;
        

        DataPokerGui(): nr_of_human_players(1), probability(0.0, 0.0), nr_of_simulation_runs(10000) {};
		~DataPokerGui(){};

		// Using default copy and move constructors. 
		DataPokerGui(const DataPokerGui& other) = default;	
		DataPokerGui& operator=(const DataPokerGui& other) = default;
		DataPokerGui(DataPokerGui&& other) noexcept = default;
		DataPokerGui& operator=(DataPokerGui&& other) noexcept = default;
    };
}// end namespace signals