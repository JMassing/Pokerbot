#pragma once

#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace parameters{

    class Config
    {
        private:

            po::options_description opts_;
            po::variables_map variables_map_;
            std::string config_file_;
           
            void setOptions();
            void parseFile();
            std::stringstream readFile(); 

        public:

            po::variables_map getConfig() {return this->variables_map_;};

            Config();
            ~Config() {};

			// Using default copy and move constructors. 
			Config(const Config& other) = default;
			Config& operator=(const Config& other) = default;
			Config(Config&& other) noexcept = default;
			Config& operator=(Config&& other) noexcept = default;

    };

}
