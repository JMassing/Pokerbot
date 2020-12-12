#pragma once

#include <random>

namespace templates{

    /**
     * @brief Checks if rhs is present within range lhs_first and lhs_last, 
     *        e.g if a vector contains a certain number 
     * 
     */
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

    /**
     * @brief 
     * Checks if rhs is present within range lhs_first and lhs_last
     * using comparison function func, e.g if a vector contains a 
     * custom class with a custom comparison function  
     * 
     * @tparam it 
     * @tparam T 
     * @tparam Compare 
     * @param lhs_first 
     * @param lhs_last 
     * @param rhs 
     * @param func 
     * @return true 
     * @return false 
     */
    template<class it, class T, class Compare>
    bool contains(it lhs_first, it lhs_last, const T& rhs, const Compare& func)
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

    /**
     * @brief Calculates squared euclidean distance between two 2D points
     * 
     * @tparam T 
     * @param pt1 
     * @param pt2 
     * @return double 
     */
    template<class T>
    double squaredEuclideanDistance2D(const T& pt1, const T& pt2)
    {
        return (pt1-pt2).x*(pt1-pt2).x+(pt1-pt2).y*(pt1-pt2).y;
    }
 
    /**
     * @brief sets value to given max or min, if it exceeds 
     * or, respectively, falls below max or min boundaries
     * 
     * @tparam T 
     * @param min 
     * @param max 
     * @param value 
     */
    template<class T>
    void enforceBoundaries(const T& min, const T& max, T& value)
    {
           value < min ? value = min : value = value;
           value > max ? value = max : value = value;      
    }

    /**
     * @brief Rolls n-sided die using random number generator rng
     * 
     * @tparam T 
     * @param n 
     * @param rng 
     * @return int 
     */
    template<class T>
    int rollDie(int n, T rng)
    {
        std::uniform_int_distribution<> dist(1, n);    
        return dist(rng);
    }
}