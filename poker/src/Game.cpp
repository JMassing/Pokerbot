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

    void Game::sortHands()
    {
        for(const Hand& hand: this->player_hands)
        { 
            std::sort(hand.hand.begin(), hand.hand.end());
        }
    }

}// end namespace poker