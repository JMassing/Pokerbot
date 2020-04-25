#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "BaseCard.h"
#include "Hand.h"
#include "Mapping.h"

namespace poker{

    class Deck{

    private:
        // this keeps track on where we are in the deck 
        int pos_tracker_;
        
    public:

        // The Deck is a vector, since we do not include the known cards (=the hand of the robot)
        // The nr. of known card changes depending on where in the game we are (start of game, flop, ...)
        std::vector<detect::BaseCard> deck_;

        explicit Deck(Hand& robot_hand);
        ~Deck() {};
                
        // Using default copy and move constructors. 
		Deck(const Deck& other) = default;	
		Deck& operator=(const Deck& other) = default;
		Deck(Deck&& other) noexcept = default;
		Deck& operator=(Deck&& other) noexcept = default;

        void shuffle();

        //@brief: Returns card in deck at pos pos_tracker and increments pos_tracker.
        detect::BaseCard pullCard()
        {
            return deck_[this->pos_tracker_++];
        };
        //@brief: Burns card in deck by incrementing pos_tracker.
        void burnCard() 
        {
            ++this->pos_tracker_;
        };
        //@brief: Returns position in deck.
        int getPosition()
        {
            return this->pos_tracker_;
        };  
        //@brief: Sets position to top of deck
        void resetPosition()
        {
            this->pos_tracker_=0;
        };
    };

}// end namespace poker