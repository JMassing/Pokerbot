#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "Card.h"
#include "Hand.h"
#include "Mapping.h"

namespace poker{

    class Deck{

    private:
        // this keeps track on where we are in the deck 
        int pos_tracker;
        
    public:

        // The Deck is a vector, since we do not include the known cards (=the hand of the robot)
        // The nr. of known card changes depending on where in the game we are (start of game, flop, ...)
        std::vector<detect::Card> deck;

        explicit Deck(Hand robot_hand);
        ~Deck() {};
                
        // Using default copy and move constructors. 
		Deck(const Deck& other) = default;	
		Deck& operator=(const Deck& other) = default;
		Deck(Deck&& other) noexcept = default;
		Deck& operator=(Deck&& other) noexcept = default;

        void shuffle();

        //@brief: Returns card in deck at pos pos_tracker and increments pos_tracker.
        detect::Card pullCard()
        {
            return deck[this->pos_tracker++];
        };
        void burnCard() 
        {
            ++this->pos_tracker;
        };
        int getPosition()
        {
            return this->pos_tracker;
        }   
        
    };

}// end namespace poker