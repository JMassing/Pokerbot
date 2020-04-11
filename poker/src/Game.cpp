#include "Game.h"


namespace poker{

    // Update Hands with knwon cards
    void Game::updateHands(std::array<detect::Card,5> public_cards, std::array<detect::Card,2> robot_cards)
    {
        // Add known cards to robot_hand_
        for(const auto& card: robot_cards)
        {
            this->robot_hand_.addToHand(card);
        }
        for(const auto& card: public_cards)
        {
            this->robot_hand_.addToHand(card);
        }

        // Add public_cards to player hands
        for(int i=0; i<this->player_hands_.size(); ++i)
        {
            for(const auto& card: public_cards)
            {
                this->player_hands_.at(i).addToHand(card);
            }
        }

    }

    //get Rankings of hands
    void Game::getHandRankings()
    {
        GetRanking get_ranking;
        // Get ranking
        get_ranking.run(this->robot_hand_);
        this->robot_hand_.ranking_=get_ranking.getRanking();
        this->robot_hand_.high_cards_=get_ranking.getHighCards();
        for(auto& hand: this->player_hands_)
        {
            get_ranking.run(hand);
            hand.ranking_=get_ranking.getRanking();
            hand.high_cards_=get_ranking.getHighCards();
        }
    }	
    
    // Compare hands and get the winner
    int Game::getWinner()
    {
        int winner=0;
        int count=0;
        this->getHandRankings();
        Hand winner_hand=this->robot_hand_;
        for(const auto& hand: this->player_hands_)
        {
            ++count;
            // compare rankings
            if(hand.ranking_>winner_hand.ranking_)
            {
                // new winner
                winner_hand=hand;
                winner=count;
            }
            else if(hand.ranking_==winner_hand.ranking_)
            {
                //compare highcards
                for(int i=0; i<hand.high_cards_.size(); ++i)
                {
                    if(hand.high_cards_.at(i) > winner_hand.high_cards_.at(i))
                    {
                        //new winner
                        winner_hand=hand;
                        winner=count;
                    }
                    else
                    {
                        // winner stays 
                    }
                    
                }
            }
            else
            {
                //winner stays
            }
        }

        return winner;
    }
   
}// end namespace poker