#pragma once


#include <utility>
#include <vector>

#include "BaseCard.hpp"

namespace detect
{
	/**
	* @class DataDetect
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Data structure containing detection module output data to poker module
	*
	* @version 1.0
	* @date 2020-11-18
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    struct DataDetect
    {

        std::vector<BaseCard> cards;

        DataDetect(): cards() {};
		~DataDetect(){};

		// Using default copy and move constructors. 
		DataDetect(const DataDetect& other) = default;	
		DataDetect& operator=(const DataDetect& other) = default;
		DataDetect(DataDetect&& other) noexcept = default;
		DataDetect& operator=(DataDetect&& other) noexcept = default;
    };
}// end namespace signals