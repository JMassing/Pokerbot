#pragma once

// observer interface design pattern after 
// https://www.c-plusplus.net/forum/topic/155350/einf%C3%BChrung-in-design-patterns

namespace gui
{
	/**  \ingroup gui
	* @class IObserver
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Observer Interface used in Observer Pattern 
	*		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/	
	class IObserver
	{
		public:
        			
            virtual void update() = 0;
			virtual ~IObserver() {};
	};
	
}//end namespace interfaces


