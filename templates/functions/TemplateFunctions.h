#pragma once
#include "Card.h"

namespace templates{

    template<class it, class T>
    bool contains(it lhs_first, it lhs_last, const T& rhs)
    {
        for(auto p = lhs_first; p != lhs_last; ++p)
        {
            if(*p == rhs)
            {
                return true;
            }
        } 
        
        return false;
    }

    template<class it, class T, class Compare>
    bool contains(it lhs_first, it lhs_last, const T& rhs, Compare& func)
    {
        for(auto p = lhs_first; p != lhs_last; ++p)
        {
            if(func(*p, rhs))
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