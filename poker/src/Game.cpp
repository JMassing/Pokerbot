#include "Game.h"

namespace poker{

    Game::Game(int nr_of_players):  nr_of_players{nr_of_players}
    {
        // at the start of the game, we don't know any cards
        Hand empty_hand;
        for(int i=0; i<nr_of_players;++i)
        {
            this->player_hands.emplace_back(empty_hand);
        }
    }

    //@brief sort cards in hands by rank in ascending order
    void Game::sortHands()
    {
        for(auto& hand: this->player_hands)
        { 
            std::sort(hand.hand.begin(), hand.hand.end(), [](const auto& lhs, const auto& rhs)
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