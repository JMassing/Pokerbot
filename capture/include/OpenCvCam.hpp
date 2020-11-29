#pragma once

#include <string>
#include <memory>

#include <opencv2/videoio.hpp>

#include "ICameraDevice.hpp"
#include "Image.hpp"

namespace capture {

	/**
	* \ingroup capture
	*  
	* @class OpenCvCam
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Wrapper for OpenCV VideoCapture class.
	*		
	* @version 1.0
	* @date 2020-11-29
	* 
	* @copyright Copyright (c) 2020
	* 
	*/

	class OpenCvCam: public ICameraDevice
	{ 
		private:
			cv::VideoCapture cap_;
			int device_ID_;
			int api_ID_;
            Image& frame_;

		public:
			
            /**
             * @brief Open video file or a capturing device or a IP video stream for video capturing.
             * 
             * @return true if connection could be opened
             * @return false if connection could not be opened
             */
            bool open() override
            {
                return this->cap_.open(this->device_ID_ + this->api_ID_);
            }
            /**
             * @brief Returns true if video capturing has been initialized already.
             * 
             * @return true 
             * @return false 
             */
            bool isOpened() override
            {
                return this->cap_.isOpened();
            }
            /**
             * @brief Read and store frame from video stream 
             * 
             * @return true 
             * @return false if no frame has been grabbed
             */
            bool read() override
            {
                return this->cap_.read(this->frame_.image);
            }
           
            bool set(const int& prop_id, const int& value) override
            {
                return this->cap_.set(prop_id, value);
            }
            double get(const int& prop_id) const override
            {
                return this->cap_.get(prop_id);
            }
            std::string getBackendName() override
            {
                return this->cap_.getBackendName();
            }
            
			OpenCvCam(
                Image& frame,
				const int& device_ID = 0, 
				const int& api_ID = cv::CAP_ANY
				):
				device_ID_(device_ID), 
				frame_{frame}, 
				cap_{}, 
				api_ID_(api_ID)
			{};

			OpenCvCam(
				const std::string& video,
                Image& frame,
				const int& device_ID = 0, 
				const int& api_ID = cv::CAP_ANY           
				): 
				frame_{frame}, 
				cap_(video), 
				device_ID_(device_ID), 
				api_ID_(api_ID) 
			{};

			~OpenCvCam() {};

			// Using default copy and move constructors. 
			OpenCvCam(const OpenCvCam& other) = default;	
			OpenCvCam& operator=(const OpenCvCam& other) = default;
			OpenCvCam(OpenCvCam&& other) noexcept = default;
			OpenCvCam& operator=(OpenCvCam&& other) noexcept = default;
			
	};

} //end namespace capture

