#include "WinnerDeterminator.hpp"

namespace poker{

    // Update Hands with known cards
    int WinnerDeterminator::determineWinner(std::vector<Hand>& player_hands, Hand& robot_hand)
    {
        // Get Hand Rankings

        RankDeterminator get_ranking;

        get_ranking.run(robot_hand);

        robot_hand.ranking_ = get_ranking.getRanking();
        robot_hand.high_cards_ = get_ranking.getHighCards();

        for(auto& hand: player_hands)
        {
            get_ranking.clear();
            get_ranking.run(hand);
            hand.ranking_ = get_ranking.getRanking();
            hand.high_cards_ = get_ranking.getHighCards();
        }

        // Determine Winner

        int winner = 0;
        int count = 0; 
        bool tie = false;

        Hand winner_hand = robot_hand;

        for(const auto& hand: player_hands)
        {
            ++count;
            // compare rankings
            if(hand.ranking_ > winner_hand.ranking_)
            {
                // new winner
                winner_hand = hand;
                winner = count;
                tie = false;
            }
            else if(hand.ranking_ == winner_hand.ranking_)
            {
                //compare highcards
                for(int i=0; i<hand.high_cards_.size(); ++i)
                {
                    if(hand.high_cards_.at(i) > winner_hand.high_cards_.at(i))
                    {
                        //new winner
                        winner_hand = hand;
                        winner = count;
                        tie = false;
                        break;
                    }
                    else if(hand.high_cards_.at(i) < winner_hand.high_cards_.at(i) && tie == false)
                    {
                        break;
                    }
                    else if( i == hand.high_cards_.size()-1 && 
                             hand.high_cards_.at(i) == winner_hand.high_cards_.at(i) )
                    {
                        //we have a tie
                        tie = true;
                    }
                    else
                    {
                        // we don't know the winner yet
                    }
                    
                }
            }
            else
            {
                //winner stays
            }
        }

        if(tie == true && winner == 0)
        {
            winner = -1;
        }
        else if(tie == true && winner != 0)
        {
            winner = -2;
        }
        else
        {
            // do nothing
        }

        return winner;
    }
} // end namespace poker