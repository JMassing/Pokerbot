#include "RankDeterminator.hpp"

#include <iostream>

namespace poker {

    namespace {

        // local function to add cards to high_cards_
        void fillHighCards(std::array<int,5>& high_cards, Hand& hand, int i)
        {
            // add remaining high cards to high_cards_
            for(const auto& card: hand.cards_)
            {
                if(!templates::contains(high_cards.begin(), high_cards.end(), card.rank))
                {
                    high_cards.at(i) = card.rank;
                    ++i;         
                                             
                    if(i>4)
                    {  
                        // we have the 5 high cards
                        break;
                    }
                    else
                    {
                        //do nothing
                    }
                }
                else
                {
                    // do nothing
                }
            }
        }
    }; // end namespace

    // @brief: Checks if we have a Pair, Two Pairs, Three Of A Kind, Four Of A Kind or a Full House
    void RankDeterminator::isMultipleOfCards(Hand& hand)
    {   
        // Counter for number of occurences of certain rank in hand. 
        // Starts at one because there is always one of the card in the hand.
        int count{1};

        // Vector of multiples in the hand. Multiples are saved as pair(nr of cards, rank of card)
        std::vector<std::pair<int,int>> multiples{};

        // Remember the last checked card rank to avoid checking the same rank multiple times
        int tmp_rank{UNKNOWN};

        // For each card in the hand, check how many of the following cards are the same. 
        // It is a sorted hand, so if the next card is not the same 
        // there are no more occurences of this card in the deck. 
        // Also we can skip cards with ranks we already have.       
        for(auto p1 = hand.cards_.begin(); p1 != hand.cards_.end()-1; ++p1)
        {
            // Make sure we havent already checked this rank and that it is not unknown
            if((*p1).rank != tmp_rank && (*p1).rank != UNKNOWN)
            {
                for(auto p2 = p1+1; p2 != hand.cards_.end(); ++p2)
                {
                    if((*p1).rank != (*p2).rank)
                    {
                        // there are no more occurences of this card in the hand
                        break;
                    }
                    else
                    {
                        ++count;
                    }
                }
            }
            else
            {
                //do nothing
            }
            if(count>1)
            {
                multiples.emplace_back(std::make_pair(count,(*p1).rank));            
            }
            else
            {
                //do nothing
            }
            // reset count to 1
            count = 1;
            // remember current card rank
            tmp_rank = (*p1).rank;
        }

        if(multiples.size() > 0)
        {
            // Sort multiples in ascending order for number of multiples
            std::sort(multiples.begin(), multiples.end(), [](const auto& lhs, const auto& rhs)
                {
                    return lhs.first > rhs.first;
                }
            );

            // switch how many multiples
            switch(multiples.size())
            {
                // only one multiple in the hand
                case 1: 
                    // check which type of multiple
                    switch(multiples.at(0).first)
                    {
                        // We have four of a kind. The highest card that matters is the four 
                        // of a kind. We can't have the same four of a kind twice
                        case 4 : 
                            this-> ranking_ = FOUR_OF_A_KIND; 
                            this->high_cards_.fill(-1);
                            this->high_cards_.at(0)=multiples.at(0).second;
                            this->high_cards_.at(1)=multiples.at(0).second;
                            this->high_cards_.at(2)=multiples.at(0).second;
                            this->high_cards_.at(3)=multiples.at(0).second;
                            fillHighCards(this->high_cards_,hand,4);
                            break;
                        // We have three of a kind. Three of a kind is first high card, 
                        // then it goes down the line.
                        case 3 : 
                            this-> ranking_ = THREE_OF_A_KIND;
                            this->high_cards_.fill(-1);
                            this->high_cards_.at(0)=multiples.at(0).second;
                            this->high_cards_.at(1)=multiples.at(0).second;
                            this->high_cards_.at(2)=multiples.at(0).second;
                            fillHighCards(this->high_cards_,hand,3);
                            break;
                        // We have a pair. Pair card is first high_card. 
                        // Then it goes down the line of high cards if we have the same pair
                        case 2 : 
                            this-> ranking_ = PAIR; 
                            this->high_cards_.fill(-1);
                            this->high_cards_.at(0)=multiples.at(0).second;
                            this->high_cards_.at(1)=multiples.at(0).second;
                            fillHighCards(this->high_cards_,hand,2);
                            break;
                    }
                break;
                // two multiples in the hand

                case 2: 
                    switch(multiples.at(0).first)
                    {
                        // We have four of a kind. The highest card that matters is the four 
                        // of a kind.
                        case 4 : 

                            this->ranking_ = FOUR_OF_A_KIND; 
                            this->high_cards_.fill(-1);
                            this->high_cards_.at(0)=multiples.at(0).second;
                            this->high_cards_.at(1)=multiples.at(0).second;
                            this->high_cards_.at(2)=multiples.at(0).second;
                            this->high_cards_.at(3)=multiples.at(0).second;
                            fillHighCards(this->high_cards_,hand,4);
                            break;

                        // We have three of a kind and another multiple, so we have a full house.
                        // The main high card is the three of a kind then the pair.
                        // We might have three of a kind twice though, so we have to check which
                        //  one is higher and counts in the full house as the triplet
                        case 3 : 

                            this->ranking_ = FULL_HOUSE;
                            this->high_cards_.fill(-1);

                            // Check if we have 2 triplets and which one is the better one
                            if( multiples.at(0).first > multiples.at(1).first || 
                                ( multiples.at(0).first == multiples.at(1).first && 
                                  multiples.at(0).second>multiples.at(1).second ) )
                            {
                                this->high_cards_.at(0)=multiples.at(0).second;
                                for(auto p = high_cards_.begin()+1; p != high_cards_.end(); ++p)
                                {
                                    *p = multiples.at(1).second;
                                }
                            }
                            else 
                            {
                                this->high_cards_.at(1)=multiples.at(1).second;
                                for(auto p = high_cards_.begin()+1; p != high_cards_.end(); ++p)
                                {
                                    *p = multiples.at(0).second;
                                }
                            }
                            break;

                        // We have two pairs. Need to check which of the pairs has the higher 
                        // card and then fill the fifth high_card with the highest remaining card 
                        // in the hand     
                        case 2 : 

                            this->ranking_ = TWO_PAIR;
                            this->high_cards_.fill(-1);

                            // Check which pair is higher
                            if(multiples.at(0).second>multiples.at(1).second)
                            {
                              
                                for(auto p = high_cards_.begin(); p != high_cards_.begin()+1; ++p)
                                {
                                    *p = multiples.at(0).second;
                                }

                                for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                {
                                    *p = multiples.at(1).second;
                                }
                            }
                            else 
                            {
                                for(auto p = high_cards_.begin(); p != high_cards_.begin()+1; ++p)
                                {
                                    *p = multiples.at(1).second;
                                }
                                
                                for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                {
                                    *p = multiples.at(0).second;
                                }
                            }

                            // Fill the 5th high card, in case we have the same two pairs
                            for(const auto& card: hand.cards_)
                            {
                              if( !templates::contains(
                                    this-> high_cards_.begin(), 
                                    this->high_cards_.end(), 
                                    card.rank
                                    ) )
                              {
                                  this-> high_cards_.at(4) = card.rank;
                                  // we have the 5 high cards
                                  break;
                              }
                              else
                              {
                                  // do nothing
                              }
                            }
                            break;
                    }
                    break;

                // We have three multiples
                case 3:
                    switch(multiples.at(0).first)
                    {
                        // can't have four of a kind in this case
                        // We have a full house with one triplet and two pairs.
                        // We need to check which pair is the higher one and 
                        // counts for the full house
                        case 3 : 

                            this-> ranking_ = FULL_HOUSE;
                            this->high_cards_.fill(-1);
                            this->high_cards_.at(0)=multiples.at(0).second;

                            // Check which pair is the higher one
                            if(multiples.at(1).second>multiples.at(2).second)
                            {
                                for(auto p = high_cards_.begin()+1; p != high_cards_.end(); ++p)
                                {
                                    *p = multiples.at(1).second;
                                }
                            }
                            else 
                            {
                                for(auto p = high_cards_.begin()+1; p != high_cards_.end(); ++p)
                                {
                                    *p = multiples.at(2).second;
                                }
                            }
                            break;

                        // We have three pairs. We have to find the two highest pairs.
                        // Then we have to fill the fifth high_card with the highest 
                        // remaining card in the deck
                        case 2 : 

                            this-> ranking_ = TWO_PAIR;
                            this->high_cards_.fill(-1);

                            if(multiples.at(0).second>multiples.at(1).second &&
                               multiples.at(0).second>multiples.at(2).second)
                            {
                                for(auto p = high_cards_.begin(); p != high_cards_.begin()+1; ++p)
                                {
                                    *p = multiples.at(0).second;
                                }
                                if(multiples.at(1).second>multiples.at(2).second)
                                {
                                    for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                    {
                                        *p = multiples.at(1).second;
                                    }
                                }
                                else
                                {
                                     for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                    {
                                        *p = multiples.at(2).second;
                                    }
                                }

                            }
                            else if(multiples.at(1).second>multiples.at(0).second && 
                                    multiples.at(1).second>multiples.at(2).second)
                            {
                                for(auto p = high_cards_.begin(); p != high_cards_.begin()+1; ++p)
                                {
                                    *p = multiples.at(1).second;
                                }
                                if(multiples.at(0).second>multiples.at(2).second)
                                {
                                    for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                    {
                                        *p = multiples.at(0).second;
                                    }
                                }
                                else
                                {
                                     for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                    {
                                        *p = multiples.at(2).second;
                                    }
                                }

                            }
                            else 
                            {
                                for(auto p = high_cards_.begin(); p != high_cards_.begin()+1; ++p)
                                {
                                    *p = multiples.at(2).second;
                                }
                                if(multiples.at(0).second>multiples.at(1).second)
                                {
                                    for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                    {
                                        *p = multiples.at(0).second;
                                    }
                                }
                                else
                                {
                                     for(auto p = high_cards_.begin()+2; p != high_cards_.begin()+3; ++p)
                                    {
                                        *p = multiples.at(1).second;
                                    }
                                }
                                
                            }
                            // add the 5th high card in case we have two same pairs
                            for(const auto& card: hand.cards_)
                            {
                              if( !templates::contains(
                                    this->high_cards_.begin(), 
                                    this->high_cards_.end(), 
                                    card.rank
                                    ) )
                              {
                                  this-> high_cards_.at(4)=card.rank;
                                  // we have the 5 high cards
                                  break;
                              }
                              else
                              {
                                  // do nothing
                              }
                            }
                            break;
                    }
                    break;
            }
        }
        else
        {
            // do nothing, no multiples of cards in this deck                
        }

    }   

    //@brief checks if we have a AceLowStraight
    bool RankDeterminator::isAceLowStreet(Hand& hand)
    {
        if( !hand.containsRank(ACE) || !hand.containsRank(TWO) || 
            !hand.containsRank(THREE) || !hand.containsRank(FOUR) || 
            !hand.containsRank(FIVE) )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

     //@brief checks if we have a Straight
    void RankDeterminator::isStraight(Hand& hand)
    {
        // make hand unique
    
        Hand unique_hand;

        for(const auto& card : hand.cards_)
        {
            if(!unique_hand.containsRank(card.rank))
            {
                unique_hand.addToHand(card);
            }
            else
            {
                //do not add card
            }            
        }
      
        for(int i=0; i<unique_hand.cards_.size()-4; ++i)
        {
            if( unique_hand.cards_.at(i).rank != UNKNOWN &&
                unique_hand.cards_.at(i).rank == unique_hand.cards_.at(i+1).rank+1 && 
                unique_hand.cards_.at(i).rank == unique_hand.cards_.at(i+2).rank+2 &&
                unique_hand.cards_.at(i).rank == unique_hand.cards_.at(i+3).rank+3 && 
                unique_hand.cards_.at(i).rank == unique_hand.cards_.at(i+4).rank+4 ) 
            {
                this->ranking_ = STRAIGHT;
                this->high_cards_.fill(-1);
                this->high_cards_.fill(unique_hand.cards_.at(i).rank);

                // exit the method            
                return;
            }    
            else
            {
                //do nothing
            }
                    
        }

        //cNo straight detected so far. Still might be an acelow straight. Let's check it.
        if(isAceLowStreet(unique_hand))
        {
            this->ranking_ = STRAIGHT;
            this->high_cards_.fill(-1);
            // high card is 5
            this->high_cards_.fill(5);
            
        }
    }

    // Counts the number of each suit we have in hand. If we have >= 5 of one kind we have a flush
    Hand RankDeterminator::isFlush(Hand& hand)
    {
        Hand flush_cards;
        int count_hearts{0};
        int count_diamonds{0};
        int count_clubs{0};
        int count_spades{0};

        for(const auto& card: hand.cards_)
        {
            switch(card.suit){
                case HEARTS : ++count_hearts; break;
                case DIAMONDS : ++count_diamonds; break;
                case CLUBS : ++count_clubs; break;
                case SPADES : ++count_spades; break;
                default : break;
            }
        }
        if(count_hearts>=5 || count_diamonds>=5 || count_clubs>=5 || count_spades>=5)
        {
            this->ranking_ = FLUSH;
            this->high_cards_.fill(-1);
            // now we have to find the high card of the flush. Check which flush first.
            int flush{};
            if(count_hearts>=5)
            {
                flush = HEARTS;
            }
            else if(count_diamonds>=5)
            {
                flush = DIAMONDS;
            }
            else if(count_clubs>=5)
            {
                flush = CLUBS;
            }
            else
            {
                flush = SPADES;
            }
           
           // here we need all cards of the flush, since we want to return them to check them 
           // for a straight (straight flush) later. Also we can add the high_cards 
           // in the same step
            int i=0;
            for(const auto& card: hand.cards_)
            {   
                if(card.suit==flush){
                    flush_cards.addToHand(card);
                    if(i<4)
                    {
                        this->high_cards_.at(i)=(card.rank);
                        ++i;
                    }
                }
            }
        }
        else
        {
            //do nothing
        }

        return flush_cards;
    }

    void RankDeterminator::run(Hand& hand)
    {
        //First we have to sort our hand
        hand.sort();
        this->ranking_ = HIGH_CARD;

        // Check if hand has multiples
        this->isMultipleOfCards(hand);

        if(this->ranking_ == FOUR_OF_A_KIND || this->ranking_ == FULL_HOUSE)
        {   
            // We can't get any higher rank for this hand
            return;
        }
     
        Hand flush_cards = this->isFlush(hand);
        
        if(this->ranking_ == FLUSH)
        {
            //Check if straight flush
            this->isStraight(flush_cards);
            if(this->ranking_ == STRAIGHT)
            {
                //Congrats, we actually have a straight flush
                this->ranking_ = STRAIGHT_FLUSH;
                return;
            }
            return;
        }
   
           // Check if isStraight
        this->isStraight(hand);

        if(this->ranking_ == HIGH_CARD)
        {
            this->high_cards_.fill(-1);
            for(int i = 0; i < high_cards_.size(); ++i)
            {
                this->high_cards_.at(i)=hand.cards_.at(i).rank;
            }
        }
        else
        {
            // do nothing
        }
    }
} //end namespace poker