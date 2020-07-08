#include "PerspectiveCorrector.hpp"

namespace detect{

    //@brief: sorts corner points given by calculateCornerPoints method to order expected by 
    //@brief: perspectiveTransformation. Start lower right corner -> going clockwise
    std::vector< cv::Point2f > PerspectiveCorrector::sortCorners(
        const std::vector< cv::Point2f >& points, 
        const cv::Point2f& center
        )
    {
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
        // Points to transform to corners of cards.image
		std::vector<cv::Point2f> ImageCorners = 
            {   
                cv::Point2f(dst.size().width - offset, +offset),
                cv::Point2f(+offset , +offset),		
			    cv::Point2f(+offset , dst.size().height - offset), 
                cv::Point2f(dst.size().width - offset, dst.size().height - offset) 
            };
        
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