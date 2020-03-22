#include "GetRanking.h"

namespace poker {

 //@brief checks if we have a AceLowStreet
    bool GetRanking::isAceLowStreet(Hand& hand)
    {
        if(!hand.containsRank(detect::ACE) || !hand.containsRank(detect::TWO) || !hand.containsRank(detect::THREE) || !hand.containsRank(detect::FOUR) || !hand.containsRank(detect::FIVE))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    
    bool GetRanking::isStraight(Hand& hand)
    {
        // make hand unique
        Hand unique_hand;

        for(const auto& card : hand.hand_)
        {
            if(!unique_hand.containsCard(card))
            {
                unique_hand.addToHand(card);
            }
            else
            {
                //do not add card
            }            
        }
        // check if straight
        for(int i=0; i<hand.hand_.size()-4; ++i)
        {
            if(unique_hand.hand_[i].rank!=detect::UNKNOWN &&
                unique_hand.hand_[i].rank==unique_hand.hand_[i+1].rank-1 && unique_hand.hand_[i].rank==unique_hand.hand_[i+2].rank-2 
                && unique_hand.hand_[i].rank==unique_hand.hand_[i+3].rank-3 && unique_hand.hand_[i].rank==unique_hand.hand_[i+3].rank-4) 
            {
                return true;
            }    
            else
            {
                //do nothing
            }
                    
        }
        return false;
    }


    bool GetRanking::isPair(Hand& hand)
    {
        for(int i=0; i<hand.hand_.size()-1; ++i)
        {
            if(hand.hand_[i].rank!=detect::UNKNOWN 
                && hand.hand_[i].rank==hand.hand_[i+1].rank)
            {
                return true;
            }
        }
        return false;
    }

    bool GetRanking::isTwoPair(Hand& hand)
    {
        return false;
    }
    
    bool GetRanking::isThreeOfAKind(Hand& hand)
    {
        for(int i=0; i<hand.hand_.size()-2; ++i)
        {
            if(hand.hand_[i].rank!=detect::UNKNOWN && 
                hand.hand_[i].rank==hand.hand_[i+1].rank && hand.hand_[i].rank==hand.hand_[i+2].rank) 
            {
                return true;
            }
        }
        return false;
    }

    bool GetRanking::isFullHouse(Hand& hand)
    {
        return false;
    }


    bool GetRanking::isFourOfAKind(Hand& hand)
    {
        for(int i=0; i<hand.hand_.size()-3; ++i)
        {
            if(hand.hand_[i].rank!=detect::UNKNOWN && 
                hand.hand_[i].rank==hand.hand_[i+1].rank && hand.hand_[i].rank==hand.hand_[i+2].rank && hand.hand_[i].rank==hand.hand_[i+3].rank) 
            {
                return true;
            }
        }
        return false;
    }

    // Counts the number of each suit we have in hand. If we have >= 5 of one kind we have a flush
    bool GetRanking::isFlush(Hand& hand)
    {

        int count_hearts{0};
        int count_diamonds{0};
        int count_clubs{0};
        int count_spades{0};

        for(const auto& card: hand.hand_)
        {
            switch(card.suit){
                case detect::HEARTS : ++count_hearts;
                case detect::DIAMONDS : ++count_diamonds;
                case detect::CLUBS : ++count_clubs;
                case detect::SPADES : ++count_spades;
            }
        }
        if(count_hearts>=5 || count_diamonds>=5 || count_clubs>=5 || count_spades>=5)
        {
            return true;
        }
        return false;
    }

    void GetRanking::FlushPath(Hand& hand)
    {

    }

    //this checks for hands that must at least have one pair in the hand. E.g. if you don't have a pair, it can't be a full house
    void GetRanking::PairPath(Hand& hand)
    {
        // Check Pair first
        if(this->isPair(hand))
        {
            this->ranking=detect::PAIR;
            if(this->isThreeOfAKind(hand))
            {
                this->ranking=detect::THREE_OF_A_KIND;
                if(this->isFourOfAKind(hand))
                {
                    this->ranking=detect::FOUR_OF_A_KIND;
                }
                else
                {
                    if(this->isFullHouse(hand))
                    {
                        this->ranking=detect::FULL_HOUSE;
                    }
                    else
                    {
                        //do nothing, this is only three of a kind
                    }                    
                }                
            }
            else
            {
                if(this->isTwoPair(hand))
                {
                    this->ranking=detect::TWO_PAIR;
                }
                else
                {
                    //do nothing. This is only a pair.
                }                
            }            
        }
        else
        {
            //do nothing. Other possibilities that don't at least have a pair are checked in different methods.
        }               
    }

    void GetRanking::checkRank(Hand& hand)
    {
        //First we have to sort our hand
        hand.sort();
        this->PairPath(hand);
    }
}//end namespace poker