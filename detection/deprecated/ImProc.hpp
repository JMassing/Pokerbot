#pragma once

#include <vector>
#include <algorithm>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace detect { namespace ImProc {

		enum Filter { LARGEST_AREA, SMALLEST_AREA, LE_AREA, GE_AREA };
			
		void calculateCornerPoints(const std::vector<std::vector<cv::Point> >& contours, std::vector < std::vector< cv::Point2f >>& corners);	// calculates corners of contours
        void findContours(const cv::Mat& src, std::vector<std::vector<cv::Point> >& contours, const int& threshold, const int& thresh_method = cv::THRESH_BINARY);
        void calculateCenterPoint(const std::vector<std::vector<cv::Point> >& contours, std::vector< cv::Point2f >& centers);					// calculates center point of contours
        void contourFilter(std::vector<std::vector<cv::Point> >& contour, const int& method = LARGEST_AREA, const double& value = 0);	                        // filter vector of contours
        bool perspectiveTransformation(const cv::Mat src, cv::Mat& dst, const std::vector< cv::Point2f >& points, const int& offset);
        std::vector< cv::Point2f > sortCorners(const std::vector< cv::Point2f >& points, const cv::Point2f& center);
        void binarizeImage(const cv::Mat & src, cv::Mat & dst, const int& threshold, const int& thresh_method);
		double compareImages(const cv::Mat &src, const cv::Mat &dst);			

} } // end namespace detect::ImageProcessor


