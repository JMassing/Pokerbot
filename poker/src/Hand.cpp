#include "Hand.h"

#include <iostream>
#include <string>

namespace poker
{
    //@brief: Checks if Hand already contains card
    bool Hand::contains(const detect::Card& card)
    {
        for(const detect::Card &hand_card : this->hand)
        {
            if(hand_card == card)
            {
                return true;
            }
        }
        return false;  
    }

    //@brief: Adds card to hand
    void Hand::addToHand(const detect::Card& card)
    {
        if(!contains(card))
        {
            for(int i=0; i<this->hand.size(); i++)
            {
                if(this->hand.at(i) == detect::Card())    //replace first unknown card in hand with  card
                {
                    this->hand.at(i) = card;
                    return;
                }
            }    
        }        
    }

    //@brief: print hand
    void Hand::print()
    {
        detect::Mapping mapping;
        for(const detect::Card& card: this->hand)
        { 
            std::string rank = mapping.text_mappings.right.at(card.rank);
			std::string	suit = mapping.text_mappings.right.at(card.suit);
			std::string	text = rank + suit + " ";
            std::cout << text;
        }
        std::cout << std::endl; 
    }
}//end namespace detect