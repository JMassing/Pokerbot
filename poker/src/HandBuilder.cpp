#include "HandBuilder.hpp"

namespace poker{

    // Update Hands with known cards
    void HandBuilder::buildHands(
                const std::vector<BaseCard>& public_cards, 
                const std::vector<BaseCard>& robot_cards,
                std::vector<Hand>& player_hands,
                Hand& robot_hand
                )
    {
        // Add known cards to robot_hand
        for(const auto& card: robot_cards)
        {
           robot_hand.addToHand(card);
        }
        for(const auto& card: public_cards)
        {
            robot_hand.addToHand(card);
        }

        // Add public_cards to player hands
        for(int i = 0; i < player_hands.size(); ++i)
        {
            for(const auto& card: public_cards)
            {
                player_hands.at(i).addToHand(card);
            }
        }
    }
} // end namespace poker