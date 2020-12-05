#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

#include <opencv2/core.hpp>
#include "TemplateFunctions.hpp"

namespace detect 
{
    /** *\ingroup detection
	* @class CornerSorter
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Sort Corners of Card images
    *  		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    class CornerSorter
	{
		public:    
            /**
            * @brief sorts corner points to orderexpected by perspectiveTransformation. 
            * Start lower right corner -> going clockwise
            * 
            */	  
            std::vector< cv::Point2f > sortCorners(
               const std::vector< cv::Point2f >& points, 
               const cv::Point2f& center
               );   

			CornerSorter(){};

			~CornerSorter(){};

			// Using default copy and move constructors. 
			CornerSorter(const CornerSorter& other) = default;	
			CornerSorter& operator=(const CornerSorter& other) = default;
			CornerSorter(CornerSorter&& other) noexcept = default;
			CornerSorter& operator=(CornerSorter&& other) noexcept = default;
					
	};

}//namespace detect