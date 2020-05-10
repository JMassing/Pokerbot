#pragma once

#include <array>
#include <vector>

#include <opencv2/core.hpp>

#include "BaseCard.h"
#include "Card.h"
#include "RectangleCorners.h"
#include "TemplateFunctions.h"

namespace detect
{
	class AssignCards
	{
	
	private:

		templates::RectangleCorners<cv::Point> robot_area_corners_;		// corner points of the area int the image where robot cards should be placed
		templates::RectangleCorners<cv::Point> public_area_corners_;	// corner points of the area in the image where public cards should be placed
		std::vector<BaseCard> public_cards_;
		std::array<BaseCard,2> robot_cards_;

		bool isInArea(const Card& card, const templates::RectangleCorners<cv::Point>& area);
				
    public:
		
		std::array<BaseCard,2> getRobotCards() {return this->robot_cards_;};
		std::vector<BaseCard> getPublicCards() {return this->public_cards_;};
		void assign(std::vector<Card>& detected_cards);

		AssignCards(templates::RectangleCorners<cv::Point>& robot_area_corners, templates::RectangleCorners<cv::Point>& public_area_corners) :
					 robot_area_corners_{robot_area_corners}, public_area_corners_{public_area_corners}, public_cards_{}, robot_cards_{} { };

		~AssignCards() {};
		
		// Use default copy and move operators
		AssignCards(const AssignCards& other) = default;	
		AssignCards& operator=(const AssignCards& other) = default;
		AssignCards(AssignCards&& other) noexcept = default;
		AssignCards& operator=(AssignCards&& other) noexcept = default;
		
	};

}