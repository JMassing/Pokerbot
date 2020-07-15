#include "MonteCarlo.hpp"

namespace poker{

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
                SimSettings& settings,
                Deck deck,
                const std::vector<BaseCard>& public_cards,
                const std::vector<BaseCard>& robot_cards,
                const bool& log_sim
                )
    {
        int nr_of_wins{0};
        int nr_of_ties_with_highest_hand{0};

        // set up logging of % of hands dealt in simulation
        std::array<int,9> hand_count{0};

        std::vector<Hand> player_hands{};
        player_hands.resize(settings.nr_of_human_players, Hand());
        Hand robot_hand{};

        // Run Monte Carlo Simulation for given nr of runs.
        for(int i = 0; i < settings.nr_of_simulation_runs; ++i)
        {
            // revert hands to build hands from scratch
            for(auto& hand: player_hands)
            {
                hand.clear();
            }
            robot_hand.clear();
            
            // holds detected public cards. If size < 5, cards will be drawn from Deck and added
            // until size == 5. These will be then added to the hands
            std::vector<BaseCard> public_cards_tmp{};
            public_cards_tmp = public_cards; 

            HandBuilder::buildHands(
                public_cards_tmp, 
                robot_cards,
                player_hands,
                robot_hand
            );

            // Step 1 reset position in deck and shuffle deck;
            deck.resetPosition();
            deck.shuffle();
            // Add hand cards to robot hand, if it is unknown
            for(int i = 0; i < 2; ++i)
            {
                if(robot_hand.hand_.at(i).rank == UNKNOWN)
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

                // first flop card dealt
                case 1: 

                    //two more flop cards
                    deck.burnCard();
                    for(int i=0; i<2; ++i)
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

                 // secons flop card dealt
                case 2: 

                    //third flop cards
                    deck.burnCard();
                    public_cards_tmp.emplace_back(deck.pullCard());
                    
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
                robot_cards,
                player_hands,
                robot_hand
            );      
           
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
                static_cast<double>(settings.nr_of_simulation_runs)*100.0, 
                static_cast<double>(nr_of_ties_with_highest_hand) /
                static_cast<double>(settings.nr_of_simulation_runs)*100.0
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
                               static_cast<double>(settings.nr_of_simulation_runs)*100.0 
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