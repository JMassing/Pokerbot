#pragma once

#include <opencv2/core.hpp>

// Wrapper class for cv::Mat. This adds operator= to cv::Mat to make sure we have a deep copy when using an copy constructor or assignment operator. 
// Image is used in different classes that might and processing might be done on the underlying images in some cases. We do not want to be surprised
// by changes in the original data, after it was copied and we do changes to the new object

namespace detect{

    struct Image{

        cv::Mat image;

        Image() : image{} { };
        ~Image() {};

        // Make sure we do a deep copy the images when we use copy constructors. Otherwise we might be surprised at some point, when doing changes to the image data.
        Image(const Image& other) noexcept : image{}
        {
            // use copy assignment operator as defined below
            *this = other;
        };	

        Image& operator=(const Image& other) noexcept
        {	
            if (this != &other)
            {
                this->image = other.image.clone();
            }
            return *this;
        };
            
        // Custom move constructors
        Image(Image&& other) noexcept : image{}
        {
            // use move assignment operator as defined below
            *this = std::move(other);
        };

        Image& operator=(Image&& other) noexcept
        {
            if (this != &other)
            {
                this->image.release();
                    
                // assignment operator for cv::Mat returns a pointer to the object, and not a deep copy
                this->image = other.image;
                    
                // releasing the old images here will decrement the ref counter, but not delete the underlying data. Other.image will point to nullptr according to cv::Mat reference
                other.image.release();
            }	
            return *this;
        };		
    };

} //end namespace detect