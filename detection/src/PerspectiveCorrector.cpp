#include "PerspectiveCorrector.hpp"
#include <iostream>

namespace detect{

    //@brief: sorts corner points given by calculateCornerPoints method to order expected by 
    //		  perspectiveTransformation. Start lower right corner -> going clockwise
    std::vector< cv::Point2f > PerspectiveCorrector::sortCorners(
        const std::vector< cv::Point2f >& points, 
        const cv::Point2f& center
        )
    {
		// We use this method of comparing to the center point, instead of a method were we
		// calculate the sum and differences of the points for sorting. This method used here
		// is more stable in highly tilted views
		std::vector< cv::Point2f > sorted_points;

		int count = 0;
		do
		{
			for (auto point : points)
			{
				switch (sorted_points.size())
				{
					case 0:
					{
						if (point.x > center.x && point.y < center.y) {
							sorted_points.emplace_back(point);
						}
						break;
					}
					case 1:
					{
						if (point.x < center.x && point.y < center.y) {
							sorted_points.emplace_back(point);
						}
						break;
					}
					case 2:
					{
						if (point.x < center.x && point.y > center.y) {
							sorted_points.emplace_back(point);
						}
						break;
					}
					case 3:
					{
						if (point.x > center.x && point.y > center.y) {
							sorted_points.emplace_back(point);
						}
						break;
					}
				}
			}
			++count;
		} while (count < 4);
		if (sorted_points.size() < 4)
		{
			sorted_points = points;
			return sorted_points;
		}

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
		// This only makes sense if we have exactly 4 Corner points
		if(points.size() == 4)
		{
			// Sort Corners
		
			std::vector< cv::Point2f > sorted_points = this->sortCorners(points, center);
			
			// Points to transform to corners of cards.image. 
			std::vector<cv::Point2f> image_corners = {};
			
			// Order of Points depend on Cards Orientation in the Image
			// First we to sort the points for their x-values, in
			// descending order to compare them.
			std::vector<cv::Point2f> descending_points = points;
			std::sort(descending_points.begin(), descending_points.end(),
				[](const auto& lhs, const auto& rhs){ return lhs.x > rhs.x; }
			);

			// We also need the pos of the points with the min and max y value
			// with respect to their x value, as well as the distance between 
			// the bottom right and top left point (distance_right) and the
			// bottom right and bottom left point (distance_left)
			int pos_min_y = 
				std::distance( descending_points.begin() , 
					std::min_element( descending_points.begin(), descending_points.end(),
					[](const auto& lhs, const auto& rhs){ return lhs.y < rhs.y; } ) 
				); 
			int pos_max_y = 
				std::distance( descending_points.begin() , 
					std::max_element( descending_points.begin(), descending_points.end(),
					[](const auto& lhs, const auto& rhs){ return lhs.y < rhs.y; } ) 
				); 
			
			double distance_right = templates::squaredEuclideanDistance2D(
				sorted_points.at(0), sorted_points.at(3)
				);
			double distance_left = templates::squaredEuclideanDistance2D(
				sorted_points.at(0), sorted_points.at(1)
				);

			// Case 1: Card is oriented more horizontally than upright and tilted to the right
			if( pos_min_y == 1 && pos_max_y == 2 && distance_right < distance_left && 
				descending_points.at(3).y < descending_points.at(0).y)
			{
				image_corners = { 
					cv::Point2f(dst.size().width - offset, dst.size().height - offset),
					cv::Point2f(dst.size().width - offset, +offset),
					cv::Point2f(+offset , +offset),							
					cv::Point2f(+offset , dst.size().height - offset)					                  		
					};
			}
			// Case 2: Card is oriented more horizontally than upright and tilted to the left
			else if(pos_min_y == 2 && pos_max_y == 1 && distance_right < distance_left && 
					descending_points.at(3).y > descending_points.at(0).y)
			{
				image_corners = { 
					cv::Point2f(dst.size().width - offset, dst.size().height - offset),
					cv::Point2f(dst.size().width - offset, +offset),
					cv::Point2f(+offset , +offset),							
					cv::Point2f(+offset , dst.size().height - offset)					                  		
					};
			}
			// Case 3: Card is oriented diamond shaped and tilted to the left
			else if(pos_min_y == 2 && pos_max_y == 1 && distance_right < distance_left && 
					descending_points.at(3).y < descending_points.at(0).y)
			{
				image_corners = { 
					cv::Point2f(dst.size().width - offset, dst.size().height - offset),			                  		
					cv::Point2f(dst.size().width - offset, +offset),
					cv::Point2f(+offset , +offset),							
					cv::Point2f(+offset , dst.size().height - offset)
					};
			}
			// Case 4: Card is upright and only slightly tilted to either side
			else
			{
				image_corners = { 
					cv::Point2f(dst.size().width - offset, +offset),
					cv::Point2f(+offset , +offset),							
					cv::Point2f(+offset , dst.size().height - offset), 
					cv::Point2f(dst.size().width - offset, dst.size().height - offset) 
					};
			}
			
			if (image_corners.size() == sorted_points.size())
			{
				cv::Mat M = cv::getPerspectiveTransform(sorted_points, image_corners);
				cv::warpPerspective(src, dst, M, dst.size());
				return true;
			}
		}

		return false;
    }
} // end namespace detect