#pragma once

#include <utility>

#include "DefaultConfig.h"

namespace shared
{
    struct DataPokerGui
    {
        int nr_of_human_players;
        std::pair<double,double> probability;
        int nr_of_simulation_runs;
        std::shared_ptr<DefaultConfig> default_config;
     
        void setToDefault()
		{
			this->nr_of_simulation_runs = default_config->nr_sim_runs;
		}

        void saveAsDefault()
		{
           default_config->nr_sim_runs = this->nr_of_simulation_runs;
           this->default_config->saveConfig();
		}

        DataPokerGui(std::shared_ptr<DefaultConfig> default_config): nr_of_human_players(1), probability(0.0, 0.0), default_config(default_config)
        {
            this->setToDefault();
        };
		~DataPokerGui(){};

		// Using default copy and move constructors. 
		DataPokerGui(const DataPokerGui& other) = default;	
		DataPokerGui& operator=(const DataPokerGui& other) = default;
		DataPokerGui(DataPokerGui&& other) noexcept = default;
		DataPokerGui& operator=(DataPokerGui&& other) noexcept = default;
    };
}// end namespace data