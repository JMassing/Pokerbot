#include "TCoordsCalculator.hpp"

namespace detect{

    std::vector<cv::Point2f> TCoordsCalculator::calc_coords(
		const std::vector<cv::Point2f>& sorted_points,
		int width,
		int height,
		int offset
		)
    {
		// Order of Points depend on Cards Orientation in the Image
		// First we to sort the points for their x-values, in
		// descending order to compare them.
		std::vector<cv::Point2f> descending_points = sorted_points;
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

		std::vector<cv::Point2f> image_corners{};
		// Case 1: Card is oriented more horizontally than upright and tilted to the right
		if( pos_min_y == 1 && pos_max_y == 2 && distance_right < distance_left && 
			descending_points.at(3).y < descending_points.at(0).y)
		{
			image_corners = { 
				cv::Point2f(width - offset, height - offset),
				cv::Point2f(width - offset, +offset),
				cv::Point2f(+offset , +offset),							
				cv::Point2f(+offset , height - offset)					                  		
				};
		}
		// Case 2: Card is oriented more horizontally than upright and tilted to the left
		else if(pos_min_y == 2 && pos_max_y == 1 && distance_right < distance_left && 
				descending_points.at(3).y > descending_points.at(0).y)
		{
			image_corners = { 
				cv::Point2f(width - offset, height - offset),
				cv::Point2f(width - offset, +offset),
				cv::Point2f(+offset , +offset),							
				cv::Point2f(+offset , height - offset)					                  		
				};
		}
		// Case 3: Card is oriented oriented diamond shaped and tilted to the left, but higly distorted (camera close to the ground)
		else if(pos_min_y == 2 && (pos_max_y == 1 || pos_max_y == 0) && distance_right < distance_left && 
				descending_points.at(3).y < descending_points.at(0).y)
		{
			image_corners = { 
				cv::Point2f(width - offset, height - offset),
				cv::Point2f(width - offset, +offset),
				cv::Point2f(+offset , +offset),							
				cv::Point2f(+offset , height - offset)					                  		
				};
		}
		// Case 4: Card is slightly diamond shaped and tilted to the right
		else if(pos_min_y == 1 && pos_max_y == 2 && distance_right < distance_left && 
				descending_points.at(3).y > descending_points.at(0).y)
		{
			image_corners = { 
				cv::Point2f(width - offset, height - offset),			                  		
				cv::Point2f(width - offset, +offset),
				cv::Point2f(+offset , +offset),							
				cv::Point2f(+offset , height - offset)
				};
		}
		// Case 5: Card horizontal, taking perspective distortion into account
		else if((pos_min_y == 1 || pos_min_y == 2) && (pos_max_y == 0 || pos_max_y == 3) && distance_right < distance_left)
		{
			image_corners = { 
				cv::Point2f(width - offset, height - offset),			                  		
				cv::Point2f(width - offset, +offset),
				cv::Point2f(+offset , +offset),							
				cv::Point2f(+offset , height - offset)
				};
		}
		// Else includes, tilted left, tilted right, dimaond shaped tilted left, diamond shaped and tilted right, upright
		else
		{
			image_corners = { 
				cv::Point2f(width - offset, +offset),
				cv::Point2f(+offset , +offset),							
				cv::Point2f(+offset , height - offset), 
				cv::Point2f(width - offset, height - offset) 
				};
		}

		return image_corners;
    }
} // end namespace detect