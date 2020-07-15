#pragma once

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// Finds contours in images
namespace detect 
{
    
	class ContourFinder
	{

		public:

            const enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };

            
            static void binarizeImage(
                const cv::Mat & src, 
                cv::Mat & dst, 
                const int& threshold, 
                const int& thresh_method
                );

            static std::vector<std::vector<cv::Point> > findContours(
                const cv::Mat& src, 
                const int& threshold, 
                const int& thresh_method = cv::THRESH_BINARY
                );
            
            static void filterContours(
                std::vector<std::vector<cv::Point> >& contour, 
                const int& method, 
                const double& value = 0
                );       

            static std::vector< cv::Point2f > calculateCenterPoints(
                const std::vector<std::vector<cv::Point> >& contours
                );			

            static std::vector < std::vector< cv::Point2f >> calculateCornerPoints(
                const std::vector<std::vector<cv::Point> >& contours
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
