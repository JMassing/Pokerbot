#pragma once

#include "IPokerDetect.hpp"
#include "DataDetect.hpp"

namespace detect {

	/** *\ingroup detection
	* @class DetectPokerInterface
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Implements communication interface between detection and poker module.
	* 		 Exposes detected cards to poker module via DataDetect data structure.
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/

	class DetectPokerInterface: public poker::IPokerDetect
	{ 
		private:

		DataDetect& data_;

		public:
			
            DataDetect getData() const override { return this->data_; };

			explicit DetectPokerInterface(DataDetect& data): 
				data_(data)
			{};

			~DetectPokerInterface() {};

			// Using default copy and move constructors. 
			DetectPokerInterface(const DetectPokerInterface& other) = default;	
			DetectPokerInterface& operator=(const DetectPokerInterface& other) = default;
			DetectPokerInterface(DetectPokerInterface&& other) noexcept = default;
			DetectPokerInterface& operator=(DetectPokerInterface&& other) noexcept = default;			
	};

} //end namespace capture