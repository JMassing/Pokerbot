#include "TrainImage.hpp"

#include <iostream>

namespace detect{

	void TrainImage::readImage(const std::string & filename)
	{
		this->image_.image = cv::imread(filename, cv::IMREAD_GRAYSCALE);
	}

	void TrainImage::readLabel(const std::string & filename)
	{
		std::size_t split_pos = filename.find_last_of("/\\");
		std::string name = filename.substr(split_pos + 1);
		split_pos = name.find_last_of(".");
		this->label_ = name.substr(0, split_pos);
	}

} //end namespace detect