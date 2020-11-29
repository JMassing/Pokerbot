#pragma once

#include <string>

namespace capture {

	/**
	*\ingroup capture
	* @class ICameraDevice
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Interface for attached cameras. 
	*		
	* @version 1.0
	* @date 2020-11-29
	* 
	* @copyright Copyright (c) 2020
	* 
	*/	
	class ICameraDevice
	{ 
		public:
			
            virtual bool open() = 0;
			virtual bool isOpened() = 0;
			virtual bool read() = 0;
            virtual bool set(const int&, const int&) = 0;
            virtual double get(const int&) const = 0;
            virtual std::string getBackendName() = 0;

			virtual ~ICameraDevice() {};
			
	};

} //end namespace capture

