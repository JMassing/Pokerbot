#include "HandBuilder.hpp"

namespace poker{

    // Update Hands with known cards
    void HandBuilder::buildHands(
                const std::vector<BaseCard>& public_cards, 
                const std::vector<BaseCard>& robot_cards,
                std::vector<Player>& players
                )
    {
        // Reset Hands to build from scratch
        for(auto& player : players)
        {
            player.hand.reset();
        }
     
        // Add public_cards to player hands
        for(int i = 0; i < players.size(); ++i)
        {
            // Add robot cards to robot_hand
            if(i == 0)
            {
                for(const auto& card: robot_cards)
                {
                    players.at(i).hand.addToHand(card);
                }
            }
            // Add public cards to player hands
            for(const auto& card: public_cards)
            {
                players.at(i).hand.addToHand(card);
            }
        }

        // sort all hands
        for(auto& player: players)
        {
            player.hand.sort();
        }
    }
} // end namespace poker