#pragma once

// observer interface design pattern after 
// https://www.c-plusplus.net/forum/topic/155350/einf%C3%BChrung-in-design-patterns

namespace interfaces
{
	class IObserver
	{
		public:
        			
            virtual void update() = 0;
			virtual ~IObserver() {};
	};
	
}//end namespace interfaces


