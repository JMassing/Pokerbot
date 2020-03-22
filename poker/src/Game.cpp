#include "Game.h"

namespace poker{

    void Game::updatePlayerHands(std::vector<Hand> player_hands)
    {
        this->player_hands_=player_hands;
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