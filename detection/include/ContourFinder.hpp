#pragma once

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

			   namespace detect 
{
    /**
	* @class ContourFinder
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Finds contours in Image
    *  		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
	class ContourFinder
	{

		public:

            enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };

            
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
            
            /**
            * @brief filters contours after given method. Value ist given according to method. \n
	        * Methods are: \n
	        * - LARGEST_AREA = 0, only keept largest contour \n
            * - SMALLEST_AREA = 1, only keep smalles contour \n
	        * - LE_AREA = 2, contour area is smaller/equal then given value \n
	        * - GE_AREA = 3, contour area is larger/equal then given value \n
             * 
             * @param contour Contours found in Image.
             * @param method Filtering method.
             * @param value Only for method 2 and 3. Gives max/min contour area. 
             */
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
