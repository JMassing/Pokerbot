#include "Deck.h"


namespace poker
{
    Deck::Deck() {
        // fill Deck with cards and point to cards initially
        int k=0;
        for(int j=15; j<=18; ++j)
        {
            for(int i=2; i<=14; ++i)
            {
                this->deck[k]=detect::Card(i,j);
                this->deck_ptr[k] = &deck[k];
                ++k;
            }
        }
    }

}//end namespace poker