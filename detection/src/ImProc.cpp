#include "ImProc.h"

namespace detect { namespace ImProc	{

	// @brief: finds contours in given image src for given binaryzation threshold and given binarization method 
	void findContours(const cv::Mat& src, std::vector<std::vector<cv::Point> >& contours, const int& threshold, const int& thresh_method)
	{
		cv::Mat edges;
		std::vector<cv::Vec4i> hierarchy;
		binarizeImage(src, edges, threshold, thresh_method);
		cv::findContours(edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));
	}

	// @brief: filters contours after given method. Value ist given according to method
	// @brief: Methods are 
	// @brief: LARGEST_AREA = 0, only keept largest contour
	// @brief: SMALLEST_AREA = 1, only keep smalles contour 
	// @brief: LE_AREA = 2, contour area is smaller/equal then given value
	// @brief: GE_AREA =3 , contour area is larger/equal then given value 
	void contourFilter(std::vector<std::vector<cv::Point> >& contours, const int& method, const double& value)
	{
		// Calculate area vector first
		std::vector<double> areas(contours.size());
		int i = 0;
		for (std::vector<cv::Point> contour : contours)
		{
			areas[i]=cv::contourArea(contour, false);
			++i;
		}

		std::vector<std::vector<cv::Point> > filtered_contours;
		// Filter Contours according to method
		if (method == LARGEST_AREA || method == SMALLEST_AREA)
		{
			// Only keep largest contour
			std::vector<double>::iterator pos;
			if (method == LARGEST_AREA)
			{
				pos = std::max_element(areas.begin(), areas.end());
			}
			// Only keep smallest contour
			else
			{
				pos = std::min_element(areas.begin(), areas.end());
			}
			filtered_contours.emplace_back(contours[std::distance(areas.begin(), pos)]);
		}
		// Filter contours by area value
		else
		{
			for (auto it = areas.begin(); it != areas.end(); ++it)
			{
				if ((method == GE_AREA && *it >= value) || (method == LE_AREA && *it <= value))
				{
					filtered_contours.emplace_back(contours[std::distance(areas.begin(), it)]);
		
				}
			}
		}

		contours.clear();
		for (auto const &contour : filtered_contours)
		{
			contours.emplace_back(contour);
		}

	}
	//@brief: calculates corner points of given contours using cv::approxPolyDP
	void calculateCornerPoints(const std::vector<std::vector<cv::Point> >& contours, std::vector < std::vector< cv::Point2f >>& corners)
	{
		double d = 0.01;

		for (auto const &contour : contours)
		{
			std::vector<cv::Point2f> corner_points;
			do
			{
				d = d + 1;
				cv::approxPolyDP(contour, corner_points, d, true);

			} while (corner_points.size() > 4);
			if (corner_points.size() > 0)
			{
				corners.emplace_back(corner_points);
			}
		}
	}

	//@brief: Returns Center Point of contour using the contour moments, calculated with cv::moments
	void calculateCenterPoint(const std::vector<std::vector<cv::Point> >& contours, std::vector< cv::Point2f >& centers)
	{
		cv::Moments M;
		for (auto const &contour : contours)
		{
			M = cv::moments(contour);
			centers.emplace_back(cv::Point2f((M.m10 / M.m00), (M.m01 / M.m00)));
		}
	
	}

	//@brief: Transforms perspectively distorted card image into 2D upright view of card
	bool perspectiveTransformation(const cv::Mat src, cv::Mat& dst, const std::vector< cv::Point2f >& points)
	{
		int offset = 5;
		// Points to transform to corners of cards.image
		std::vector<cv::Point2f> ImageCorners = { cv::Point2f(dst.size().width - offset, +offset),cv::Point2f(+offset , +offset),							
			cv::Point2f(+offset , dst.size().height - offset), cv::Point2f(dst.size().width - offset, dst.size().height - offset) };

		if (ImageCorners.size() == points.size())
		{
			cv::Mat M = cv::getPerspectiveTransform(points, ImageCorners);
			cv::warpPerspective(src, dst, M, dst.size());
			return true;
		}

		return false;
	}

	//@brief: sorts corner points given by calculateCornerPoints method to order expected by perspectiveTransformation. 
	//@brief: Start lower right corner -> going clockwise
	std::vector< cv::Point2f > sortCorners(const std::vector< cv::Point2f >& points, const cv::Point2f& center)
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

	//@brief: binarize given image 
	void binarizeImage(const cv::Mat & src, cv::Mat & dst, const int& threshold, const int& thresh_method)
	{
		cv::cvtColor(src, dst, cv::COLOR_RGB2GRAY);
		cv::Scalar temp_mean = cv::mean(dst);											// calculates mean image intensity. will be added to threshold to correct for lighting
		int mean_image_intensity = static_cast<int>(temp_mean[0]);
		//cv::threshold(dst, dst, mean_image_intensity + threshold, 255, thresh_method);
		cv::threshold(dst, dst, threshold, 255, thresh_method);

	}

	//@brief: Compares given images using L2_Norm and returns similarity
	double compareImages(const cv::Mat &src, const cv::Mat &dst)
	{
		if (src.size() == dst.size() && src.type() == dst.type())
		{
			 // Calculate the L2 relative error between images.
			double errorL2 = cv::norm(src, dst, cv::NORM_L2);
			// Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
			double similarity = errorL2 / static_cast<double>(src.rows * src.cols);
			return similarity;
		}
		else
		{
			return { -1 };
		}

	}

} } // namespace detect::ImProc