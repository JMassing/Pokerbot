#include "MoneyTracker.hpp" 

namespace poker{

    void MoneyTracker::processBet()
    {
        for(auto& player : this->data_.players)
        {
            // process player money
            player.money_in_play += player.current_bet;
            player.current_bet = 0;          
        }; 
    }

    void MoneyTracker::calcPotSize()
    {
        this->data_.pot_size = 0;
        for(const auto& player : this->data_.players)
        {
            this->data_.pot_size += player.money_in_play;
        }
    }

    bool MoneyTracker::hasPlayerLessThanBigblind(int big_blind)
    {
           for(const auto& player: this->data_.players)
        {
            if(player.money < big_blind)
            {
                return true;
            }
        }
        return false;
    }

    bool MoneyTracker::isPlayerAllIn()
    {
        for(auto& player: this->data_.players)
        {
            if(player.money <= 0)
            {
                player.is_all_in = true;
                return true;
            }
        }
        return false;
    }

}// end namespace poker