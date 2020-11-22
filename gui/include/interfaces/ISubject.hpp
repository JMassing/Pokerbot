#pragma once

// Base subject design pattern after 
// https://www.c-plusplus.net/forum/topic/155350/einf%C3%BChrung-in-design-patterns

#include <list>
#include <memory>
#include "IObserver.hpp"

namespace gui
{
	/**  \ingroup gui
	* @class ISubject
	* @author Julian Massing (julimassing@gmail.com)
	* @brief Subject Interface used in Observer Pattern 
	*		
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/	
	class ISubject
	{
		private:

			std::list<std::shared_ptr<IObserver>> observers_;

		public:

			void attach(std::shared_ptr<IObserver> observer);
			void detach(std::shared_ptr<IObserver> observer);
			void notify() const;

			virtual ~ISubject() {};

		protected:

			// protected to make this an abstract class
			ISubject() {};
	};

}//end namespace interfaces


