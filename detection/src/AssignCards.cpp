#include "AssignCards.h"

namespace detect {

	// @brief: assigns detected cards to robot cards and public cards
	void AssignCards::assign(std::vector<Card>& detected_cards)
	{
		this->public_cards_.clear();
		this->robot_cards_.clear();

		for(const auto& card: detected_cards)
		{	
				if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->robot_area_corners_)
					&& !templates::contains(this->robot_cards_.begin(), this->robot_cards_.end(), card))
				{
					if(this->robot_cards_.size()<2)
					{
						this->robot_cards_.emplace_back(card);
					}
				}
				else if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->public_area_corners_) &&
						!templates::contains(this->public_cards_.begin(), this->public_cards_.end(), card))
				{
					if(this->public_cards_.size()<5)
					{
						this->public_cards_.emplace_back(card);
					}
				}
				else
				{
					//do nothing
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