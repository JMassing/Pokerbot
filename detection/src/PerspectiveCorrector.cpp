#include "PerspectiveCorrector.hpp"
#include <iostream>

namespace detect{

    //@brief: sorts corner points given by calculateCornerPoints method to order expected by 
    //@brief: perspectiveTransformation. Start lower right corner -> going clockwise
    std::vector< cv::Point2f > PerspectiveCorrector::sortCorners(
        const std::vector< cv::Point2f >& points, 
        const cv::Point2f& center
        )
    {
        std::vector< cv::Point2f > sorted_points{};

		// The bottom left point has the smalles sum of its coordinates,
		// whereas the top right has the largest. The top left has
		// the smallest difference, the bottom right has the largest. 
		std::vector<int> sum{};
		std::vector<int> diff{};
		for(const auto& point: points)
		{
			sum.emplace_back(point.x + point.y);
			diff.emplace_back(point.x - point.y);
		}

		// Add points 
		// bottom right
		sorted_points.emplace_back(
			points.at(std::distance(diff.begin(),std::max_element(diff.begin(), diff.end())))
			);
		
		// bottom left
		sorted_points.emplace_back(
			points.at(std::distance(sum.begin(),std::min_element(sum.begin(), sum.end())))
			);

		// top left	
		sorted_points.emplace_back(
			points.at(std::distance(diff.begin(),std::min_element(diff.begin(), diff.end())))
			);
		
		// top right
		sorted_points.emplace_back(
			points.at(std::distance(sum.begin(),std::max_element(sum.begin(), sum.end())))
			);		

		return sorted_points;
    }

	//@brief: Transforms perspectively distorted card image into 2D upright view of card
    bool PerspectiveCorrector::warpImage(
        const cv::Mat src, 
        cv::Mat& dst, 
        const std::vector< cv::Point2f >& points, 
        const cv::Point2f& center,
        const int& offset
        )
    {

        // Points to transform to corners of cards.image
		std::vector<cv::Point2f> ImageCorners = 
            {   
                cv::Point2f(dst.size().width - offset, +offset),
                cv::Point2f(+offset , +offset),		
			    cv::Point2f(+offset , dst.size().height - offset), 
                cv::Point2f(dst.size().width - offset, dst.size().height - offset)                		
            };

		// Sort Corners
	
		std::vector< cv::Point2f > sorted_points = this->sortCorners(points, center);
		
		if (ImageCorners.size() == sorted_points.size())
		{
			cv::Mat M = cv::getPerspectiveTransform(sorted_points, ImageCorners);
			cv::warpPerspective(src, dst, M, dst.size());
			return true;
		}

		return false;
    }
} // end namespace detect