#pragma once

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "Image.hpp"

namespace detect 
{
    
	class ContourFinder
	{

		private:

            void binarizeImage(
                const cv::Mat & src, 
                cv::Mat & dst, 
                const int& threshold, 
                const int& thresh_method
                );

		public:

            enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };

            std::vector<std::vector<cv::Point> > findContours(
                const cv::Mat& src, 
                const int& threshold, 
                const int& thresh_method = cv::THRESH_BINARY
                );
            
            void filterContours(
                std::vector<std::vector<cv::Point> >& contour, 
                const int& method, 
                const double& value = 0
                );                     

			ContourFinder(){};

			~ContourFinder(){};

			// Using default copy and move constructors. 
			ContourFinder(const ContourFinder& other) = default;	
			ContourFinder& operator=(const ContourFinder& other) = default;
			ContourFinder(ContourFinder&& other) noexcept = default;
			ContourFinder& operator=(ContourFinder&& other) noexcept = default;
					
	};

}//namespace detect
