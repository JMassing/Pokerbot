#include "Simulation.hpp"

#include <iostream>
#include <fstream>

namespace poker{
  
    //@brief: Runs the simulation. Return value is a pair of probabilities. pair.first gives 
    // the probability to outright win with the robot hand. pair.second gives the probability 
    // for the robot to have the highest ranking hand but tie with another player 
    void Simulation::run()
    {
    
        int nr_of_wins{0};
        int nr_of_ties_with_highest_hand{0};

        // update player hands size according to nr. of human players received from gui
        this->data_.player_hands.resize(this->settings_.nr_of_human_players, Hand());
        
        // build hands with known cards
        HandBuilder::buildHands(
            this->detected_cards_.public_cards, 
            this->detected_cards_.robot_cards,
            this->data_.player_hands,
            this->data_.robot_hand
            );
        
        // set up logging of % of hands dealt in simulation
        std::array<int,9> hand_count{0};
        
        // Make the deck, without the robot cards
        Deck deck(this->data_.robot_hand);

        // Run Monte Carlo Simulation for given nr of runs.
        for(int i = 0; i < this->settings_.nr_of_simulation_runs; ++i)
        {
             // revert hands to build hands from scratch
            for(auto& hand: this->data_.player_hands)
            {
                hand.clear();
            }
            this->data_.robot_hand.clear();
            
            // holds detected public cards. If size < 5, cards will be drawn from Deck and added
            // until size == 5. These will be then added to the hands
            std::vector<detect::BaseCard> public_cards_tmp{};
            public_cards_tmp = this->detected_cards_.public_cards; 

            HandBuilder::buildHands(
                public_cards_tmp, 
                this->detected_cards_.robot_cards,
                this->data_.player_hands,
                this->data_.robot_hand
            );

            // Step 1 reset position in deck and shuffle deck;
            deck.resetPosition();
            deck.shuffle();
            // Add hand cards to robot hand, if it is unknown
            for(int i = 0; i < 2; ++i)
            {
                if(this->data_.robot_hand.hand_.at(i).rank==detect::UNKNOWN)
                {
                    this->data_.robot_hand.addToHand(deck.pullCard());
                }
            }

            // Add hand cards to player hands;
            for(auto& hand : this->data_.player_hands)
            {
                hand.addToHand(deck.pullCard()); // add first hand card
                hand.addToHand(deck.pullCard()); // add second hand card
            }

            // simulate flop, turn, river if not dealt
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

            // update hands with simulated drawn public cards
            HandBuilder::buildHands(
                public_cards_tmp, 
                this->detected_cards_.robot_cards,
                this->data_.player_hands,
                this->data_.robot_hand
            );      
           
            // determine winner from hands
            int winner =  WinnerDeterminator::determineWinner(
                this->data_.player_hands, 
                this->data_.robot_hand
                );
            
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
                ++hand_count.at(this->data_.robot_hand.ranking_);
                this->logRun(winner);
            }

            // reset hands with known cards
            HandBuilder::buildHands(
                this->detected_cards_.public_cards, 
                this->detected_cards_.robot_cards,
                this->data_.player_hands,
                this->data_.robot_hand
            );    

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
                    logfile << static_cast<double>(i) << ": " 
                            << static_cast<double>(hand_count.at(i)) /
                               static_cast<double>(this->settings_.nr_of_simulation_runs)*100.0 
                            << "%" << std::endl;
                }
                logfile.close();
            }
            else
            {
                std::cerr << "Error: Could not write to log file. File could not be opened." 
                          << std::endl;
            }  
        }

        this->data_.probability = 
            std::make_pair(
                static_cast<double>(nr_of_wins) /
                static_cast<double>(this->settings_.nr_of_simulation_runs)*100.0, 
                static_cast<double>(nr_of_ties_with_highest_hand) /
                static_cast<double>(this->settings_.nr_of_simulation_runs)*100.0
                );       
    }

    void Simulation::logRun(const int& winner)
    {
        std::ofstream logfile;
        logfile.open("simlog.txt", std::ios::app);
        if(logfile.is_open())
        {
            std::string robot_hand = this->data_.robot_hand.print().str();
            // print robot hand to file, erase last character, since it is a \n and we don't
            //  want a line break here
            logfile << winner << ";" 
                    << robot_hand.erase(robot_hand.size()-1) 
                    << ";" << this->data_.robot_hand.ranking_ << ";";

            for(auto& hand: this->data_.player_hands)
            {
                std::string hand_string = hand.print().str();
                logfile << hand_string.erase(hand_string.size()-1) 
                        << ";" << hand.ranking_ << ";"; 
            } 
            logfile << std::endl;
            logfile.close();
        }
        else
        {
            std::cerr << "Error: Could not write to log file. File could not be opened."
                      << std::endl;
        }   
    }
}// end namespace poker