#include "Simulation.h"

#include <iostream>
#include <fstream>

namespace poker{

    // Update Hands with known cards
    void Simulation::updateHands(const std::vector<detect::BaseCard>& public_cards, const std::vector<detect::BaseCard>& robot_cards)
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

        if(tie==true && winner==0)
        {
            winner=-1;
        }
        else if(tie==true && winner!=0)
        {
            winner=-2;
        }
        else
        {
            // do nothing
        }

        return winner;
    }
    
    // Runs the simulation. Return value is a pair of probabilities. pair.first gives the probability to outright win with the robot hand. 
    // pair.second gives the probability for the robot to have the highest ranking hand but tie with another player 
    void Simulation::run()
    {
       
        int nr_of_wins{0};
        int nr_of_ties_with_highest_hand{0};

        // update player hands size according to nr. of human players received from gui
        this->player_hands_.resize(this->data_gui_->nr_of_human_players, Hand());
        
        // Run Monte Carlo Simulation for nr_of_iterations_ iterations.
        this->updateHands(this->data_detect_->public_cards, this->data_detect_->robot_cards);
        
        // set up logging of % of hands dealt in simulation
        std::array<int,9> hand_count{0};
        
        // Make the deck, without the robot cards
        Deck deck(this->robot_hand_);

        for(int i=0; i<this->data_gui_->nr_of_simulation_runs; ++i)
        {
            std::vector<detect::BaseCard> public_cards_tmp{};
            public_cards_tmp=this->data_detect_->public_cards;
            // update hands with known cards
            this->updateHands(public_cards_tmp, this->data_detect_->robot_cards);         
            
            // Step 1 reset position in deck and shuffle deck;
            deck.resetPosition();
            deck.shuffle();
            // Add hand cards to robot hand, if it is unknown
            for(int i=0; i<2; ++i)
            {
                if(this->robot_hand_.hand_.at(i).rank==detect::UNKNOWN)
                {
                    this->robot_hand_.addToHand(deck.pullCard());
                }
            }
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
            // update hands with drawn public cards
            this->updateHands(public_cards_tmp, this->data_detect_->robot_cards);
           
            // determine winner from hands
            int winner=this->determineWinner();
            
            if(winner==0)
            {
                ++nr_of_wins;
            } 
            else if(winner==-1)
            {
                ++nr_of_ties_with_highest_hand;
            }
            else
            {
                //do nothing
            }

            // sim logging
            if(this->log_sim_==true)
            {
                ++hand_count.at(this->robot_hand_.ranking_);
                this->logRun(winner);
            }

            // revert hands
            for(auto& hand: this->player_hands_)
            {
                hand.clear();
            }
            this->robot_hand_.clear();
     
        }
        
        // log hands 
        if(this->log_sim_==true)
        {
            std::ofstream logfile;
            logfile.open("simlog.txt", std::ios::app);
            if(logfile.is_open())
            {
                for(int i=0; i<hand_count.size(); ++i)
                {
                    logfile << static_cast<double>(i) << ": " << static_cast<double>(hand_count.at(i))/static_cast<double>(this->data_gui_->nr_of_simulation_runs)*100.0 << "%" << std::endl;
                }
                logfile.close();
            }
            else
            {
                std::cerr << "Error: Could not write to log file. File could not be opened." << std::endl;
            }  
        }

        this->data_gui_->probability = 
            std::make_pair(static_cast<double>(nr_of_wins)/static_cast<double>(this->data_gui_->nr_of_simulation_runs)*100.0, 
                static_cast<double>(nr_of_ties_with_highest_hand)/static_cast<double>(this->data_gui_->nr_of_simulation_runs)*100.0);
        
    }

    void Simulation::logRun(const int& winner)
    {
        std::ofstream logfile;
        logfile.open("simlog.txt", std::ios::app);
        if(logfile.is_open())
        {
            std::string robot_hand = robot_hand_.print().str();
            // print robot hand to file, erase last character, since it is a \n and we don't want a line break here
            logfile << winner << ";" << robot_hand.erase(robot_hand.size()-1) << ";" << this->robot_hand_.ranking_ << ";";
            for(auto& hand: this->player_hands_)
            {
                std::string hand_string = hand.print().str();
                logfile << hand_string.erase(hand_string.size()-1) << ";" << hand.ranking_ << ";"; 
            } 
            logfile << std::endl;
            logfile.close();
        }
        else
        {
            std::cerr << "Error: Could not write to log file. File could not be opened." << std::endl;
        }   
    }
}// end namespace poker