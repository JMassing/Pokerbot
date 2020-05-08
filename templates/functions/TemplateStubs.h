#pragma once
#include "Card.h"

namespace templates{

    template<class T>
    bool contains(detect::Card input_card, T cards)
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

}