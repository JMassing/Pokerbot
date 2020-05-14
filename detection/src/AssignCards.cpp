#include "AssignCards.h"

namespace detect {

	// @brief: assigns detected cards to robot cards and public cards
	void AssignCards::assign(std::vector<Card>& detected_cards)
	{
		for(const auto& card: detected_cards)
		{	
			for(auto& robot_card : this->robot_cards_)
			{
				if(card.rank != UNKNOWN && card.suit != UNKNOWN && robot_card.rank == UNKNOWN && isInArea(card, this->robot_area_corners_)
					&& !templates::contains(this->robot_cards_.begin(), this->robot_cards_.end(), card))
				{
					robot_card=card;
				}
				else if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->public_area_corners_) && !templates::contains(this->public_cards_.begin(), this->public_cards_.end(), card))
				{
					this->public_cards_.emplace_back(card);
				}
			}	
		}		
	}


	bool AssignCards::isInArea(const Card& card, const templates::RectangleCorners<cv::Point>& area)
	{
		if(card.center_point.x < area.upper_right.x && card.center_point.x > area.upper_left.x 
			&& card.center_point.y < area.upper_left.y && card.center_point.y > area.lower_left.y)
		{
			return true;
		}
		return false;
	}

}