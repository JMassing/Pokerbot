#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include "Hand.hpp"
#include "BaseCard.hpp"
#include "Mapping.hpp"
#include "TemplateFunctions.hpp"

namespace poker{

    /**  \ingroup poker
	 * @class RankDeterminator
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Determines rank of given Hand       
	 *
	 * @version 1.0
	 * @date 2020-11-22
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
    class RankDeterminator{
        
        private:

            int ranking_;
            /**
             * @brief  5 highest cards in hand (only card rank). Starting with highest card and decreasing.
             * If you have a pair, the first two cards will be the cards of the pair and then the 
             * next highest card. If you have a straight, all five cards will be the highest card 
             * of the straight, since it is the only one that counts. Etc. ... 
             */
            std::array<int,5> high_cards_;

            void isMultipleOfCards(Hand& hand); 

            void isStraight(Hand& hand);

            bool isAceLowStreet(Hand& hand);

            Hand isFlush(Hand& hand);                        

        public:

             // Checks Ranks
            void run(Hand& hand);

            int getRanking(){ return this->ranking_; };

            std::array<int,5> getHighCards(){ return this->high_cards_; };

            void clear()
            {
                this->ranking_=-1;
                this->high_cards_.fill(0);
            }
            
            RankDeterminator():ranking_{-1}, high_cards_{-1} {};
            ~RankDeterminator() {};

            // Using default copy and move constructors. 
            RankDeterminator(const RankDeterminator& other) = default;	
            RankDeterminator& operator=(const RankDeterminator& other) = default;
            RankDeterminator(RankDeterminator&& other) noexcept = default;
            RankDeterminator& operator=(RankDeterminator&& other) noexcept = default;

    };

}// end namespace poker