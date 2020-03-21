#include "Game.h"

namespace poker{

    void Game::updatePlayerHands(std::vector<Hand> player_hands)
    {
        this->player_hands_=player_hands;
    }

    //@brief sort cards in hands by rank in ascending order
    void Game::sortHands()
    {
        for(auto& hand: this->player_hands_)
        { 
            std::sort(hand.hand_.begin(), hand.hand_.end(), [](const auto& lhs, const auto& rhs)
                {
                    return lhs.rank < rhs.rank;
                }
            );
        }
    }

    //@brief checks if we have a AceLowStreet
    bool Game::isAceLowStreet(Hand& hand)
    {
        if(!hand.containsRank(detect::ACE))
        {
            return false;
        }
        else
        {
            if(hand.containsRank(detect::TWO) && hand.containsRank(detect::THREE) && hand.containsRank(detect::FOUR) && hand.containsRank(detect::FIVE))
            {
                return true;   
            }
            else
            {
                return false;
            }
        }
    }
}// end namespace poker