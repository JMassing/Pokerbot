#include "ContourFinder.hpp"

namespace detect{

    // @brief: filters contours after given method. Value ist given according to method
	// @brief: Methods are 
	// @brief: LARGEST_AREA = 0, only keept largest contour
	// @brief: SMALLEST_AREA = 1, only keep smalles contour 
	// @brief: LE_AREA = 2, contour area is smaller/equal then given value
	// @brief: GE_AREA = 3, contour area is larger/equal then given value 
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
	void binarizeImage(
        const cv::Mat & src, 
        cv::Mat & dst, 
        const int& threshold, 
        const int& thresh_method
        )
	{
		cv::cvtColor(src, dst, cv::COLOR_RGB2GRAY);
		cv::threshold(dst, dst, threshold, 255, thresh_method);
	}

   	//@brief: Finds Contours in given image using cv::findContours method. Given Image is binarized
    //@brief: using given binarization threshold and given thresholding method (default is cv::THRESH_BINARY)
    std::vector<std::vector<cv::Point> > findContours(
        const cv::Mat& src, 
        const int& threshold,
        const int& thresh_method
        )
	{
        std::vector<std::vector<cv::Point> > contours;
		cv::Mat edges;
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

}// end namespace detect