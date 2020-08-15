#pragma once

#include <vector>

#include <opencv2/core.hpp>

#include "Card.hpp"
#include "BaseCard.hpp"
#include "TemplateFunctions.hpp"

// Assigns detected cards in image to robot cards or public cards
namespace detect 
{
    class CardAssigner
	{

        private: 

   			bool isInArea(const Card& card, const cv::Rect& area);

            // area where to place the robot cards and public cards in the image
            cv::Rect robot_area_;           
            cv::Rect public_area_;          

		public:    

            void assignCards(
                const std::vector<Card>& cards,
                std::vector<BaseCard>& public_cards,
                std::vector<BaseCard>& robot_cards
                );

			CardAssigner(
                cv::Rect robot_area,           
                cv::Rect public_area 
                ):
                robot_area_(robot_area),
                public_area_(public_area)
            {};
			~CardAssigner(){};

			// Using default copy and move constructors. 
			CardAssigner(const CardAssigner& other) = default;	
			CardAssigner& operator=(const CardAssigner& other) = default;
			CardAssigner(CardAssigner&& other) noexcept = default;
			CardAssigner& operator=(CardAssigner&& other) noexcept = default;
					
	};

}//namespace detect