#pragma once
#include "Card.h"

namespace templates{

    template<class it, class T>
    bool contains(it first, it last, const T& input)
    {
        for(auto p = first; p != last; ++p)
        {
            if(*p == input)
            {
                return true;
            }
        } 
        
        return false;
    }

    template<class it, class T, class Compare>
    bool contains(it first, it last, const T& input, Compare& func)
    {
        for(auto p = first; p != last; ++p)
        {
            if(func(*p, input))
            {
                return true;
            }
        } 
        
        return false;
    }


    template<class T>
    double squaredEuclideanDistance2D(const T& pt1, const T& pt2)
    {
        return (pt1-pt2).x*(pt1-pt2).x+(pt1-pt2).y*(pt1-pt2).y;
    }
}