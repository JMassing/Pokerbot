#include "Simulation.h"

#include <iostream>


namespace poker{

    // Update Hands with knwon cards
    void Simulation::updateHands(const std::vector<detect::Card>& public_cards, const std::array<detect::Card,2>& robot_cards)
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

    //@brief: get Rankings of hands
    void Simulation::determineHandRankings()
    {
        GetRanking get_ranking;
        // Get ranking
        get_ranking.run(this->robot_hand_);
        this->robot_hand_.ranking_=get_ranking.getRanking();
        this->robot_hand_.high_cards_=get_ranking.getHighCards();
        for(auto& hand: this->player_hands_)
        {
            get_ranking.clear();
            get_ranking.run(hand);
            hand.ranking_=get_ranking.getRanking();
            hand.high_cards_=get_ranking.getHighCards();
        }
    }	
    
    //@brief: Compare hands and get the winner. -1 signals a tie, 0 signals the robot wins, >0 is one of the players
    int Simulation::determineWinner()
    {
        int winner=0;
        int count=0;
        bool tie=false;
        this->determineHandRankings();

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
                tie=false;
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
                        tie=false;
                        break;
                    }
                    else if(hand.high_cards_.at(i) < winner_hand.high_cards_.at(i) && tie==false)
                    {
                        break;
                    }
                    else if(i==hand.high_cards_.size()-1 && hand.high_cards_.at(i) == winner_hand.high_cards_.at(i))
                    {
                        //we have a tie
                        tie=true;
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

        if(tie==true)
        {
            winner=-1;
        }

        return winner;
    }
    
    // Runs the simulation
    double Simulation::run(const std::vector<detect::Card>& public_cards, const std::array<detect::Card,2>& robot_cards)
    {
       
        double nr_of_wins{0};
        // Run Monte Carlo Simulation for nr_of_iterations_ iterations.
        std::vector<detect::Card> public_cards_tmp{};
        this->updateHands(public_cards, robot_cards);
        // Make the remaining deck
        Deck deck(this->robot_hand_);
        for(int i=0; i<this->nr_of_iterations_-1; ++i)
        {
            public_cards_tmp=public_cards;
            // update hands with known cards;
            this->updateHands(public_cards_tmp, robot_cards);         
            
            // Step 1 shuffle deck;
            deck.shuffle();
            // Add hand cards to player hands;
            for(auto& hand : this->player_hands_)
            {
                hand.addToHand(deck.pullCard()); // add first hand card
                hand.addToHand(deck.pullCard()); // add second hand card
            }
            // flop, turn, river
            switch(public_cards_tmp.size())
            {
                // pre flop
                case 0: 
                    // flop
                    deck.burnCard();
                    for(int i=0; i<3; ++i)
                    {
                        public_cards_tmp.emplace_back(deck.pullCard());
                    }
                    // turn
                    deck.burnCard();
                    public_cards_tmp.emplace_back(deck.pullCard());
                    // river
                    deck.burnCard();
                    public_cards_tmp.emplace_back(deck.pullCard());
                    break;
                // pre river
                case 3:
                    // turn
                    deck.burnCard();
                    public_cards_tmp.emplace_back(deck.pullCard());
                    // river
                    deck.burnCard();
                    public_cards_tmp.emplace_back(deck.pullCard());
                    break;
                // pre river
                case 4:
                    // river
                    deck.burnCard();
                    public_cards_tmp.emplace_back(deck.pullCard());
                    break;
            }
            // update hands with drawn public cards and clear drawn public cards
            this->updateHands(public_cards_tmp, robot_cards);
            public_cards_tmp.clear();

            // determine winner from hands
            int winner=this->determineWinner();

            // revert hands
            for(auto& hand: this->player_hands_)
            {
                hand.clear();
            }
            this->robot_hand_.clear();

            if(winner==0)
            {
                ++nr_of_wins;
            }       
        
        }
        return nr_of_wins/static_cast<double>(this->nr_of_iterations_)*100.0;
        
    }
}// end namespace poker