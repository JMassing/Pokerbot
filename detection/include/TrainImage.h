#pragma once

#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class TrainImage
{
	private:
		cv::Mat image_;
		std::string label_;

		void readImage(const std::string & filename);
		void readLabel(const std::string & filename);		

	public:

		cv::Mat getImage() { return this->image_; }
		std::string getLabel() { return this->label_; }

		TrainImage();
		explicit TrainImage(const std::string & filename);
		~TrainImage();		
		
		// Delete copy constructor, we only need each TrainImage once. Also cv::Mat only does shallow copying and processing the copy then changes
		// the original. A .clone() function could be considered, but we only need TrainImage once.
		TrainImage(const TrainImage &other) = delete;
		TrainImage& operator=(const TrainImage& other) = delete;

		// Custom move constructors
		TrainImage(TrainImage &&other) noexcept : image_{}, label_{} 
		{		
			*this = std::move(other);
		};

		TrainImage& operator =(TrainImage &&other) noexcept
		{
			if (this != &other)
			{
				//Free the existing image 
				this->image_.release();
				
				this->image_ = other.image_; // assignment operator for cv::Mat returns a pointer to the object, and not a deep copy
				this->label_.swap(other.label_);

				other.image_.release();
				other.label_.clear();
							
			}
			return *this;
		};

};

