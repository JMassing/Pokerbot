#include "ISubject.h"

namespace interfaces
{
    void ISubject::attach(std::shared_ptr<IObserver> observer)
    {
        this->observers_.push_back(observer);
    }

    void ISubject::detach(std::shared_ptr<IObserver> observer)
    {
        this->observers_.remove(observer);
    }

    void ISubject::notify() const 
    {
        for(auto iter = this->observers_.begin(); iter != this->observers_.end(); ++iter)
        {
            (*iter)->update();
        }
    }
}