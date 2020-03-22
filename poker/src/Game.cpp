#include "Game.h"

namespace poker{

    void Game::updatePlayerHands(std::vector<Hand> player_hands)
    {
        this->player_hands_=player_hands;
    }

   
}// end namespace poker