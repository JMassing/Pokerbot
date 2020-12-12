#pragma once

#include <vector>

#include <opencv2/core.hpp>

#include "BaseCard.hpp"
#include "TemplateFunctions.hpp"

namespace poker 
{
	/**
     * \defgroup poker
	 * The Poker module manages the actual game of poker. It gets the players decisions from user input and calculates
	 * the robot decsisions based on player decision and probability of winning. The probability of winning is calculated
	 * from a monte carlo simulation based on the current robot hand and nr. of opponents.
 	 * @{
	 * @class CardAssigner
	 * @author Julian Massing (julimassing@gmail.com)
	 * @brief Assigns detected cards in image to robot cards or public cards
	 *
	 * @version 1.0
	 * @date 2020-11-21
	 * 
	 * @copyright Copyright (c) 2020
	 * 
	 */
	 /**@}*/
    class CardAssigner
	{         

		public:    

            static void assignCards(
                const std::vector<BaseCard>& cards,
                std::vector<BaseCard>& public_cards,
                std::vector<BaseCard>& robot_cards, 
                int game_phase
                );

			CardAssigner(){};
			~CardAssigner(){};

			// Using default copy and move constructors. 
			CardAssigner(const CardAssigner& other) = default;	
			CardAssigner& operator=(const CardAssigner& other) = default;
			CardAssigner(CardAssigner&& other) noexcept = default;
			CardAssigner& operator=(CardAssigner&& other) noexcept = default;
					
	};

}//namespace detect