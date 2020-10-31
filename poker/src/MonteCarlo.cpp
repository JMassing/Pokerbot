#include "MonteCarlo.hpp"

namespace poker{

    namespace{
        // local function to add public card from deck to robot_hand and player hands. 
        void addCardFromDeck(Hand& robot_hand, std::vector<Hand>& player_hands, const BaseCard& card)
        {
            robot_hand.addToHand(card);
            for(auto& player_hand: player_hands)
            {
                player_hand.addToHand(card);
            }
        }
    }

    void MonteCarlo::logRun(const int& winner, std::vector<Hand> player_hands, Hand robot_hand)
    {
        std::ofstream logfile;
        logfile.open("simlog.txt", std::ios::app);
        if(logfile.is_open())
        {
            std::string robot_hand_str = robot_hand.print().str();
            // print robot hand to file, erase last character, since it is a \n and we don't
            //  want a line break here
            logfile << winner << ";" 
                    << robot_hand_str.erase(robot_hand_str.size()-1) 
                    << ";" << robot_hand.ranking_ << ";";

            for(auto& hand: player_hands)
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

    std::pair<double,double> MonteCarlo::run(
                const int& iterations,
                Deck deck,
                const std::vector<Player>& players,
                const int& game_phase,
                const bool& log_sim
                )
    {
        int nr_of_wins{0};
        int nr_of_ties_with_highest_hand{0};

        // set up logging of % of hands dealt in simulation
        std::array<int,9> hand_count{0};
        Hand robot_hand{};
        std::vector<Hand> player_hands{};

        // Run Monte Carlo Simulation for given nr of runs.
        for(int i = 0; i < iterations; ++i)
        {

            robot_hand.reset();
            player_hands.clear();
            
            robot_hand = players.at(0).hand;            
            for(int i = 1; i < players.size(); ++i)
            {
                player_hands.emplace_back(players.at(i).hand);
            }           

            // Step 1 reset position in deck and shuffle deck;
            deck.resetPosition();
            deck.shuffle();
            // Add hand cards to robot hand, if it is unknown
            for(int i = 0; i < 2; ++i)
            {
                if(robot_hand.cards_.at(i).rank == UNKNOWN)
                {
                    robot_hand.addToHand(deck.pullCard());
                }
            }

            // Add hand cards to player hands;
            for(auto& hand : player_hands)
            {
                hand.addToHand(deck.pullCard()); // add first hand card
                hand.addToHand(deck.pullCard()); // add second hand card
            }

            // simulate flop, turn, river if not dealt       
            // pre flop
            if(game_phase == HAND_CARDS || game_phase == BET_HAND)
            {
                 // flop
                deck.burnCard();
                for(int i=0; i<3; ++i)
                {
                    addCardFromDeck(robot_hand, player_hands, deck.pullCard());
                }

                // turn
                deck.burnCard();
                addCardFromDeck(robot_hand, player_hands, deck.pullCard());

                // river
                deck.burnCard();
                addCardFromDeck(robot_hand, player_hands, deck.pullCard());
            }
            // pre turn
            else if(game_phase == FLOP || game_phase == BET_FLOP)
            {
                    // turn
                    deck.burnCard();
                    addCardFromDeck(robot_hand, player_hands, deck.pullCard());

                    // river
                    deck.burnCard();
                    addCardFromDeck(robot_hand, player_hands, deck.pullCard());

                    // add more cards, this is only necessary while flop is
                    // being dealt and we have less than 3 flop cards    
                    for(int i=0; i<3; ++i)
                    {
                        addCardFromDeck(robot_hand, player_hands, deck.pullCard());
                    }
            }
            // pre river
            else if(game_phase == TURN || game_phase == BET_TURN)
            {

                    // river
                    deck.burnCard();
                    addCardFromDeck(robot_hand, player_hands, deck.pullCard());
            }
            else
            {
                // all cards are known
            }
          
            // determine winner from hands
            int winner =  WinnerDeterminator::determineWinner(
                player_hands, 
                robot_hand
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
            if(log_sim==true)
            {
                ++hand_count.at(robot_hand.ranking_);
                logRun(winner, player_hands, robot_hand);
            }

        }

         std::pair<double,double> probability = 
            std::make_pair(
                static_cast<double>(nr_of_wins) /
                static_cast<double>(iterations)*100.0, 
                static_cast<double>(nr_of_ties_with_highest_hand) /
                static_cast<double>(iterations)*100.0
                );       

        // log hands 
        if(log_sim == true)
        {
            std::ofstream logfile;
            logfile.open("simlog.txt", std::ios::app);
            if(logfile.is_open())
            {
                for(int i=0; i<hand_count.size(); ++i)
                {
                    logfile << static_cast<double>(i) << ": " 
                            << static_cast<double>(hand_count.at(i)) /
                               static_cast<double>(iterations)*100.0 
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

        return probability;
        
    }
}// end namespace poker