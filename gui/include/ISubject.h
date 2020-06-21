#pragma once

// Base subject design pattern after https://www.c-plusplus.net/forum/topic/155350/einf%C3%BChrung-in-design-patterns

#include <list>
#include <memory>
#include "IObserver.h"

namespace interfaces
{
	class ISubject
	{
		private:

			std::list<std::shared_ptr<IObserver>> observers_;

		public:

			void attach(std::shared_ptr<IObserver> observer);
			void detach(std::shared_ptr<IObserver> observer);
			void notify();

			virtual ~ISubject() = default;

		protected:

			// protected to make this an abstract class
			ISubject() {};
	};

}//end namespace interfaces


