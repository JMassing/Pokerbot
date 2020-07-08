#include "CardAssigner.hpp"

namespace detect{

    // @brief: assigns cards to robot cards or public cards, depending on where in the image
    // the card is placed
	void CardAssigner::assignCards(
        const std::vector<Card>& cards,
        std::vector<detect::Card>& public_cards,
        std::vector<detect::Card>& robot_cards
        )
	{
		public_cards.clear();
		robot_cards.clear();

		for(const auto& card: cards)
		{	
				if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->robot_area_)
					&& !templates::contains(robot_cards.begin(), robot_cards.end(), card))
				{
					if(robot_cards.size()<2)
					{
						robot_cards.emplace_back(card);
					}
				}
				else if(card.rank != UNKNOWN && card.suit != UNKNOWN && isInArea(card, this->public_area_) &&
						!templates::contains(public_cards.begin(), public_cards.end(), card))
				{
					if(public_cards.size() < 5)
					{
						public_cards.emplace_back(card);
					}
				}
				else
				{
					//do nothing
				}	
		}		
	}

    bool CardAssigner::isInArea(const Card& card, const cv::Rect& area)
	{

		if(card.center_point.x > area.x && card.center_point.x < area.x + area.width 
			&& card.center_point.y > area.y && card.center_point.y < area.y + area.height)
		{
			return true;
		}
		return false;
	}

}