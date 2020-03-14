#include "Deck.h"

namespace poker
{
    Deck::Deck(std::array<detect::Card,2> robot_starting_cards): pos_tracker{0} {
        // fill Deck with cards and point to cards initially
        int k=0;
        for(int j=15; j<=18; ++j)
        {
            for(int i=2; i<=14; ++i)
            {
                if(robot_starting_cards[0]==detect::Card(i,j) || robot_starting_cards[1]==detect::Card(i,j))
                {
                    // do not add card to the deck, which is already dealt to the robot
                    continue;
                }
                this->deck[k]=detect::Card(i,j);
                ++k;
            }
        }
    }

    //@brief: shuffles the deck using std::shuffle function
    void Deck::shuffle()
    {        
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(this->deck.begin(), this->deck.end(),g);
    }

}//end namespace poker