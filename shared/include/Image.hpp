#pragma once

#include <opencv2/core.hpp>



    /** \ingroup shared
	* @class Image
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Wrapper  for cv::Mat. This makes sure we have a deep copy when using a copy constructor or 
    *        an assignment operator. Image is used in different modules where image processing is done on the 
    *        underlying image in some cases. We do not want to be surprised by changes in the original data, 
    *        after it was copied and we apply changes to the new image object.
	*		
	* @version 1.0
	* @date 2020-11-22
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    struct Image{

        cv::Mat image;

        Image() : image{} { };
        explicit Image(cv::Mat img) : image{img} { };
        
        bool operator==(const Image& other) const
		{
            cv::Mat dst{};
			cv::bitwise_xor(this->image, other.image, dst);  
            return cv::countNonZero(dst) == 0;
		};
	    bool operator!=(const Image& other) const
		{
            cv::Mat dst{};
			cv::bitwise_xor(this->image, other.image, dst);  
            return cv::countNonZero(dst) > 0;
		};
        
        ~Image() {};
        /**
         * @brief Custom copy constructor to get deep copy
         * 
         * @param other 
         */
        Image(const Image& other) noexcept : image{}
        {
            // use copy assignment operator as defined below
            *this = other;
        };	
        /**
         * @brief Custom copy assignment operator to get deep copy
         * 
         * @param other 
         */
        Image& operator=(const Image& other) noexcept
        {	
            if (this != &other)
            {
                this->image = other.image.clone();
            }
            return *this;
        }; 
        /**
         * @brief Custom move constructor 
         * 
         * @param other 
         */
        Image(Image&& other) noexcept : image{}
        {
            *this = std::move(other);
        }
         /**
         * @brief Custom move assignment operator
         * 
         * @param other 
         */
        Image& operator=(Image&& other) noexcept
        {
            if (this != &other)
            {
                this->image.release();                    
                // assignment operator for cv::Mat returns a pointer to the object, 
                // and not a deep copy
                this->image = other.image;                    
                // releasing the old images here will decrement the ref counter, but 
                // not delete the underlying data. Other.image will point to nullptr 
                // according to cv::Mat reference
                other.image.release();
            }	
            return *this;
        };		
    };

