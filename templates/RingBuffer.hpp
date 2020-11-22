#pragma once

#include <utility>

namespace templates{

    /**
	* @class RingBuffer
	* @author Julian Massing (julimassing@gmail.com)
	* @brief RingBuffer Pattern 
	*
	* @version 1.0
	* @date 2020-11-21
	* 
	* @copyright Copyright (c) 2020
	* 
	*/
    template<class T, std::size_t N>
    class RingBuffer
    {    
    
    protected:

        // Buffer size is net-size+1, we leave the last slot empty to differ
        // between a full and an empty buffer
        std::array<T, N+1> data_;  
        std::size_t iput_;
        std::size_t iget_;
        static std::size_t wrap(std::size_t idx) // wrap around 
        { 
            return idx % (N+1);
        }
    
    public:
       
        bool empty() const
        {
            return iput_ == iget_ ;
        }
        bool full() const
        {
            return wrap(iput_+1) == iget_;
        }
        std::size_t size() const 
        {
            return iput_ >= iget_
                ? iput_ - iget_
                : iput_ + (N+1) - iget_; 
        }
        void put(const T&);
        void get(T&);
        T peek(std::size_t) const;

        RingBuffer(): iput_(0), iget_(0) {};
    };

    template<class T, std::size_t N>
    void RingBuffer<T, N>::get(T &e)
    {
        assert(!empty());
        e = this->data_.at(this->iget_);
        this->iget_ = wrap(this->iget_+1);
    }

    template<class T, std::size_t N>
    T RingBuffer<T, N>::peek(std::size_t offset) const 
    {
        assert(offset < this->size());
        return this->data_.at(wrap(this->iget_ + offset));
    }

    template<class T, std::size_t N>
    void RingBuffer<T, N>::put(const T &e)
    {
        if(full())
        {
            this->iget_ = wrap(this->iget_+1);
        }
        assert(!full());
        this->data_.at(this->iput_) = e;
        this->iput_ = wrap(this->iput_ + 1);
    }


} // end namespace templates