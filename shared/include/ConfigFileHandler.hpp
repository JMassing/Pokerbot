#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

	/** \ingroup shared
	* @class ConfigFileHandler
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Loads the config.ini file
	*		
	* @version 1.0
	* @date 2020-11-22
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
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

            explicit ConfigFileHandler();
            ~ConfigFileHandler() {};

			// Using default copy and move constructors. 
			ConfigFileHandler(const ConfigFileHandler& other) = default;
			ConfigFileHandler& operator=(const ConfigFileHandler& other) = default;
			ConfigFileHandler(ConfigFileHandler&& other) noexcept = default;
			ConfigFileHandler& operator=(ConfigFileHandler&& other) noexcept = default;

    };


