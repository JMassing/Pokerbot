#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "BaseCard.hpp"
#include "Hand.hpp"

namespace poker{
    /**  \ingroup poker
	 * @class Deck
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Object representing a deck of cards.        
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class Deck{

    private:
        // this keeps track on where we are in the deck 
        int pos_tracker_;
        
    public:

        // The Deck is a vector, since we do not include the known cards (= the hand of the robot)
        // The nr. of known card changes depending on where in the game we are (start of game, flop, ...)
        std::vector<BaseCard> deck_;
        /**
         * @brief Shuffle the deck
         * 
         */
        void shuffle();
        /**
         * @brief Pull a card from the deck.
         * 
         */
        BaseCard pullCard()
        {
            return deck_[this->pos_tracker_++];
        };
        /**
         * @brief Burn a card from the deck.
         * 
         */       
        void burnCard() 
        {
            ++this->pos_tracker_;
        };
        /**
         * @brief Get the position in the deck
         * 
         * @return int 
         */
        int getPosition()
        {
            return this->pos_tracker_;
        };  
        /**
         * @brief Sets position to top of deck
         * 
         */
        void resetPosition()
        {
            this->pos_tracker_ = 0;
        };

        explicit Deck(Hand& robot_hand);
        ~Deck() {};
                
        // Using default copy and move constructors. 
		Deck(const Deck& other) = default;	
		Deck& operator=(const Deck& other) = default;
		Deck(Deck&& other) noexcept = default;
		Deck& operator=(Deck&& other) noexcept = default;

    };

}// end namespace poker