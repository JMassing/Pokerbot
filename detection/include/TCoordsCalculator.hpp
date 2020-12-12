#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "TemplateFunctions.hpp"
#include "CornerSorter.hpp"

namespace detect 
{
    /** *\ingroup detection
	 * @class TCoordsCalculator
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Calculates the coordinates to which the image corners should be warped depending on image orientation
     *  		
	 * @version 1.0
	 * @date 2020-12-05
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class TCoordsCalculator
	{

		public:
            /**
             * @brief Calculate coords the card corners should be transformed to
             * 
             * @param sorted_points Corners of Image sorted clockwise from lower right corner
             * @param width of destination image
             * @param height of destination image
             * @param offset in pixel. Coordinates are moved inside the image by offset
             * @return std::vector<cv::Point2f> Coordinates corner should be transformed to
             */
            std::vector<cv::Point2f> calc_coords(
                const std::vector<cv::Point2f>& sorted_points,
		        int width,
		        int height,
		        int offset
                );         
			TCoordsCalculator(){};
			~TCoordsCalculator(){};

			// Using default copy and move constructors. 
			TCoordsCalculator(const TCoordsCalculator& other) = default;	
			TCoordsCalculator& operator=(const TCoordsCalculator& other) = default;
			TCoordsCalculator(TCoordsCalculator&& other) noexcept = default;
			TCoordsCalculator& operator=(TCoordsCalculator&& other) noexcept = default;
					
	};

}//namespace detect