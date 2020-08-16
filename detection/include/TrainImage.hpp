#pragma once

#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "Image.hpp"

// Data Structure for training images
namespace detect {

	class TrainImage
	{
		private:
			std::string label_;
			Image image_;

			void readImage(const std::string & filename);
			void readLabel(const std::string & filename);		

		public:

			
			Image getImage() const { return this->image_; } 
			void setImage(Image image){this->image_ = image;}
			std::string getLabel() const { return this->label_; }

			TrainImage(){};
			explicit TrainImage(const std::string & filename)
			{
				this->readImage(filename);
				this->readLabel(filename);
			};
			~TrainImage(){};		
			
				// Using default copy and move constructors. 
			TrainImage(const TrainImage &other) = default;
			TrainImage& operator=(const TrainImage& other) = default;
			TrainImage(TrainImage &&other) noexcept = default;
			TrainImage& operator =(TrainImage &&other) noexcept = default;
	};

} //end namespace detect

