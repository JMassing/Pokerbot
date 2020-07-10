#pragma once

#include <fstream>
#include <iostream>
#include <sstream>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace shared
{

    class ConfigFileHandler
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
            void writeFile(std::stringstream& file_content);

            ConfigFileHandler();
            ~ConfigFileHandler() {};

			// Using default copy and move constructors. 
			ConfigFileHandler(const ConfigFileHandler& other) = default;
			ConfigFileHandler& operator=(const ConfigFileHandler& other) = default;
			ConfigFileHandler(ConfigFileHandler&& other) noexcept = default;
			ConfigFileHandler& operator=(ConfigFileHandler&& other) noexcept = default;

    };

}
