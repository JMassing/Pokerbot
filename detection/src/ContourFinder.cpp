#include "ContourFinder.hpp"

namespace detect{

	void ContourFinder::filterContours(
        std::vector<std::vector<cv::Point> >& contours, 
        const int& method, 
        const double& value
        )
	{
		// Calculate area vector first
		std::vector<double> areas(contours.size());
		int i = 0;
		for (std::vector<cv::Point> contour : contours)
		{
			areas.at(i)=cv::contourArea(contour, false);
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

    //@brief: binarize given image 
	void ContourFinder::binarizeImage(
        const cv::Mat & src, 
        cv::Mat & dst, 
        const int& threshold, 
        const int& thresh_method
        )
	{
		cv::cvtColor(src, dst, cv::COLOR_RGB2GRAY);
		cv::threshold(dst, dst, threshold, 255, thresh_method);
	}

   	//@brief: Finds Contours in given image using cv::findContours method. Given Image 
    //		  is binarized using given binarization threshold and given thresholding method 
	//		  (default is cv::THRESH_BINARY)
    std::vector<std::vector<cv::Point> > ContourFinder::findContours(
        const cv::Mat& src, 
        const int& threshold,
        const int& thresh_method
        )
	{
       
		cv::Mat edges;
		std::vector<std::vector<cv::Point> > contours;
		std::vector<cv::Vec4i> hierarchy;
		
		binarizeImage(src, edges, threshold, thresh_method);

		cv::findContours(
            edges, 
            contours, 
            hierarchy, 
            cv::RETR_TREE, 
            cv::CHAIN_APPROX_NONE, 
            cv::Point(0, 0)
            );

        return contours;
	}

	//@brief: calculates corner points of given contours using cv::approxPolyDP
	std::vector < std::vector< cv::Point2f >> ContourFinder::calculateCornerPoints(
		const std::vector<std::vector<cv::Point> >& contours
		)
	{
		double d = 0.01;

		std::vector < std::vector< cv::Point2f >> corners{};

		for (auto const &contour : contours)
		{
			std::vector<cv::Point2f> corner_points;
			do
			{
				d = d + 0.1;
				cv::approxPolyDP(contour, corner_points, d, true);

			} while (corner_points.size() > 4);
			
			if (corner_points.size() > 0)
			{
				corners.emplace_back(corner_points);
			}
		}

		return corners;
	}

	//@brief: Returns Center Points of contours using the contour moments, calculated with cv::moments
	std::vector< cv::Point2f > ContourFinder::calculateCenterPoints(
		const std::vector<std::vector<cv::Point> >& contours
		)
	{
		std::vector< cv::Point2f > centers{};

		cv::Moments M;

		for (auto const &contour : contours)
		{
			M = cv::moments(contour);
			centers.emplace_back(cv::Point2f((M.m10 / M.m00), (M.m01 / M.m00)));
		}
		
		return centers;
	}


}// end namespace detect