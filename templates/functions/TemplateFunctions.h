#pragma once
#include "Card.h"

namespace templates{

    template<class T>
    bool contains(const detect::Card& input_card, const T& cards)
    {
        for(const auto& card: cards)
        {
            if(card.rank==input_card.rank && card.suit==input_card.suit)
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