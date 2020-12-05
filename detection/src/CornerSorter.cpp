 #include "CornerSorter.hpp"

namespace detect 
{

  std::vector< cv::Point2f > CornerSorter::sortCorners(
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
}