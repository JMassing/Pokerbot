#pragma once

#include <vector>
#include <cmath>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace detect 
{
    class PerspectiveCorrector
	{

        private: 

            std::vector< cv::Point2f > sortCorners(
               const std::vector< cv::Point2f >& points, 
               const cv::Point2f& center
               );  

		public:    

           bool warpImage(
                const cv::Mat src, 
                cv::Mat& dst, 
                const std::vector< cv::Point2f >& points, 
                const cv::Point2f& center,
                const int& offset
                );


			PerspectiveCorrector(){};

			~PerspectiveCorrector(){};

			// Using default copy and move constructors. 
			PerspectiveCorrector(const PerspectiveCorrector& other) = default;	
			PerspectiveCorrector& operator=(const PerspectiveCorrector& other) = default;
			PerspectiveCorrector(PerspectiveCorrector&& other) noexcept = default;
			PerspectiveCorrector& operator=(PerspectiveCorrector&& other) noexcept = default;
					
	};

}//namespace detect