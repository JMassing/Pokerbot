#include "PerspectiveCorrector.hpp"

namespace detect{

    bool PerspectiveCorrector::warpImage(
        const cv::Mat src, 
        cv::Mat& dst, 
        const std::vector< cv::Point2f >& points, 
        const cv::Point2f& center,
        const int& offset
        )
    {
		// This only makes sense if we have exactly 4 Corner points and src and dst image are not empty
		if(points.size() == 4 && !src.empty() && !dst.empty())
		{
			// Sort Corners
		
			std::vector< cv::Point2f > sorted_points = this->sorter_.sortCorners(points, center);
			
			std::vector<cv::Point2f> image_corners 
				= coords_calc_.calc_coords(sorted_points, dst.size().width, dst.size().height, offset);
			
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