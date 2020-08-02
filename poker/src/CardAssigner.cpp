#include "CardAssigner.hpp"

namespace poker{

    // @brief: assigns cards to robot cards or public cards, depending on where in the image
    // 		   the card is placed
	void CardAssigner::assignCards(
        const std::vector<BaseCard>& cards,
    	std::vector<BaseCard>& public_cards,
        std::vector<BaseCard>& robot_cards, 
        int game_phase
        )
	{
		public_cards.clear();

		// Cards are transformed into BaseCards by object slicing in this step.
		// Robot cards and public cards are used only in poker module, which 
		// only needs Cards rank and suit

		// if game is in first phase, dealing hand cards, detected cards are part of 
		// robot hand.
		if(game_phase == 1)
		{
			for(const auto& card: cards)
			{	
				if( card.rank != UNKNOWN && card.suit != UNKNOWN && 
					!templates::contains(robot_cards.begin(), robot_cards.end(), card) )
				{
					if(robot_cards.size()<2)
					{
						robot_cards.emplace_back(card);
					}
				}				
				else
				{
					//do nothing
				}	
			}
		}	
		else
		{
			for(const auto& card: cards)
			{	
			
				if( card.rank != UNKNOWN && card.suit != UNKNOWN &&
					!templates::contains(public_cards.begin(), public_cards.end(), card) && 
					!templates::contains(robot_cards.begin(), robot_cards.end(), card) )
				{
					if(public_cards.size() < 5)
					{
						public_cards.emplace_back(card);
					}
				}
			}
		}
			
	}

}