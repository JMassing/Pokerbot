#pragma once

#include <vector>

#include <opencv2/core.hpp>

#include "BaseCard.hpp"
#include "TemplateFunctions.hpp"

// Assigns detected cards in image to robot cards or public cards
namespace poker 
{
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