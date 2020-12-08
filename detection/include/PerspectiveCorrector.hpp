#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "TemplateFunctions.hpp"
#include "CornerSorter.hpp"
#include "TCoordsCalculator.hpp"

namespace detect 
{
    /** *\ingroup detection
	* @class PerspectiveCorrector
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Warps given image to correct for perspective errors and get a birdseye view of card image
    *  		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    class PerspectiveCorrector
	{

        private: 

            TCoordsCalculator coords_calc_;
            CornerSorter sorter_;

		public:              
           
           /**
            * @brief Transforms perspectively distorted card image into 2D upright view of card
            * 
            * 
            * @param src Source image
            * @param dst Destination image
            * @param points Corner points of card image
            * @param center Center point of card image
            * @param offset Pixel offset to edge.
            * @return true if image coulde be transformed
            * @return false if image could not be transformed
            */
           bool warpImage(
                const cv::Mat src, 
                cv::Mat& dst, 
                const std::vector< cv::Point2f >& points, 
                const cv::Point2f& center,
                const int& offset
                );

			PerspectiveCorrector(): sorter_(), coords_calc_() {};

			~PerspectiveCorrector(){};

			// Using default copy and move constructors. 
			PerspectiveCorrector(const PerspectiveCorrector& other) = default;	
			PerspectiveCorrector& operator=(const PerspectiveCorrector& other) = default;
			PerspectiveCorrector(PerspectiveCorrector&& other) noexcept = default;
			PerspectiveCorrector& operator=(PerspectiveCorrector&& other) noexcept = default;
					
	};

}//namespace detect