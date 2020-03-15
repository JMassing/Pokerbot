#include "Hand.h"

#include <iostream>
#include <string>

namespace poker
{
    //@brief: Checks if Hand already contains card
    bool Hand::containsCard(const detect::Card& card)
    {
        for(const auto& hand_card : this->hand)
        {
            if(hand_card == card)
            {
                return true;
            }
        }
        return false;  
    }

    //@brief: Checks if Hand contains rank 
    bool Hand::containsRank(const int& rank)
    {
        for(const auto& hand_card : this->hand)
        {
            if(hand_card.rank == rank)
            {
                return true;
            }
        }
        return false;  
    }

     //@brief: Checks if Hand contains suit 
    bool Hand::containsSuit(const int& suit)
    {
        for(const auto& hand_card : this->hand)
        {
            if(hand_card.suit == suit)
            {
                return true;
            }
        }
        return false;  
    }

    //@brief: Adds card to hand
    void Hand::addToHand(const detect::Card& card)
    {
        if(!containsCard(card))
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

    //@brief: returns a sstream with the current hand
    std::stringstream Hand::print()
    {
        detect::Mapping mapping;
        std::stringstream out;
        for(const auto& card: this->hand)
        { 
            std::string rank = mapping.text_mappings.right.at(card.rank);
			std::string	suit = mapping.text_mappings.right.at(card.suit);
			std::string	text = rank + suit + " ";
            out << text;
        }
        out << std::endl; 
        return out;
    }

}//end namespace detect