#include "Hand.hpp"

#include <iostream>
#include <string>

namespace poker
{
    //@brief: Checks if Hand already contains card
    bool Hand::containsCard(const BaseCard& card)
    {
        return templates::contains(this->cards_.begin(), this->cards_.end(), card);
    }

    //@brief: Checks if Hand contains rank 
    bool Hand::containsRank(const int& rank)
    {
        return templates::contains(this->cards_.begin(), this->cards_.end(), rank, 
                    [](const auto& lhs, const auto& rhs)
                    {
                        return lhs.rank == rhs;
                    }
                );
    }

     //@brief: Checks if Hand contains suit 
    bool Hand::containsSuit(const int& suit)
    {
        return templates::contains(this->cards_.begin(), this->cards_.end(), suit, 
                    [](const auto& lhs, const auto& rhs)
                    {
                        return lhs.suit == rhs;
                    }
                );
    }

    //@brief: Adds card to hand
    void Hand::addToHand(const BaseCard& card)
    {
        if(!this->containsCard(card))
        {
            for(int i=0; i<this->cards_.size(); i++)
            {
                //replace first unknown card in hand with card
                if(this->cards_.at(i) == BaseCard())    
                {
                    this->cards_.at(i) = card;
                    return;
                }
            }    
        }        
    }

    //@brief: returns a sstream with the current hand
    std::stringstream Hand::print()
    {
        Mapping mapping;
        std::stringstream out;
        for(const auto& card: this->cards_)
        { 
            std::string rank = mapping.text_mappings.right.at(card.rank);
			std::string	suit = mapping.text_mappings.right.at(card.suit);
			std::string	text = rank + suit + " ";
            out << text;
        }
        out << std::endl; 
        return out;
    }

    //@brief sort cards in hand by rank in ascending order
    void Hand::sort()
    {
        std::sort(this->cards_.begin(), this->cards_.end(), [](const auto& lhs, const auto& rhs)
            {
                return lhs.rank > rhs.rank;
            }
        );
        
    }

    void Hand::reset()
    {
        for(auto& card : this->cards_)
        {
            card = BaseCard(UNKNOWN, UNKNOWN);
        }

        this->high_cards_.fill(UNKNOWN);
    }

}//end namespace poker