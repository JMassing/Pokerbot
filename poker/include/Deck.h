#pragma once

#include <algorithm>
#include <random>

#include "Card.h"
#include "Mapping.h"

namespace poker{

    class Deck{

    private:
        // this keeps track on where we are in the deck 
        int pos_tracker;
        
    public:

        // There are only 50 cards in the deck since we know which 2 cards the robot has
        std::array<detect::Card,50> deck;

        explicit Deck(std::array<detect::Card,2> robot_starting_cards);
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