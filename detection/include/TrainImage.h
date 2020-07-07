#pragma once

#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "Image.hpp"
namespace detect {

	class TrainImage
	{
		private:
			Image image_;
			std::string label_;

			void readImage(const std::string & filename);
			void readLabel(const std::string & filename);		

		public:

			cv::Mat getImage() { return this->image_.image; }
			std::string getLabel() { return this->label_; }

			TrainImage();
			explicit TrainImage(const std::string & filename);
			~TrainImage();		
			
			// Delete copy constructor, we only need each TrainImage once. Also cv::Mat only does shallow copying and processing the copy then changes
			// the original. A .clone() function could be considered, but we only need TrainImage once.
			TrainImage(const TrainImage &other) = default;
			TrainImage& operator=(const TrainImage& other) = default;

			// Custom move constructors
			TrainImage(TrainImage &&other) noexcept = default;
			TrainImage& operator =(TrainImage &&other) noexcept = default;
	};

} //end namespace detect

