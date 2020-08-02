#include "Deck.hpp"

#include <random>       // std::default_random_engine

namespace poker
{
    Deck::Deck(Hand& robot_hand): pos_tracker_{0} {
        // fill Deck with cards and point to cards initially
        for(int j=15; j<=18; ++j)
        {
            for(int i=2; i<=14; ++i)
            {   
                if(robot_hand.containsCard(BaseCard(i,j)))
                {
                    // do not add card to the deck, which is already dealt to the robot, i.e 
                    // it's either one of the two hand cards or dealt in flop/turn/river
                }
                else
                {
                    //add card to deck
                    this->deck_.emplace_back(BaseCard(i,j));
                }                
            }
        }
    }

    //@brief: shuffles the deck using std::shuffle function
    void Deck::shuffle()
    {        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(this->deck_.begin(), this->deck_.end(), g);
    }

}//end namespace poker