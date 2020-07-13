#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <utility>

#include "Hand.hpp"
#include "Deck.hpp"
#include "BaseCard.hpp"
#include "Mapping.hpp"
#include "RankDeterminator.hpp"
#include "Simulation.hpp"
#include "HelperFunctions.hpp"
#include "WinnerDeterminator.hpp"
#include "HandBuilder.hpp"
#include "SimSettings.hpp"
#include "DataDetect.hpp"

namespace fs = boost::filesystem;

namespace UnitTest
{
	GTEST_TEST(TestPoker,TestHand)
	{
			poker::Hand hand;
			// Test initialization of hand
			std::string test_string{"?? ?? ?? ?? ?? ?? ?? \n"};
			std::array<detect::BaseCard,7> test_hand;
			test_hand.fill(detect::BaseCard());
			ASSERT_EQ(hand.print().str(), test_string);
			ASSERT_EQ(hand.hand_, test_hand);

			// Add a card
			detect::BaseCard card1(3,15);
			hand.addToHand(card1);
			test_hand[0]=card1;
			test_string="3D ?? ?? ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);

			// Add another card
			detect::BaseCard card2(5,15);
			hand.addToHand(card2);
			test_hand[1]=card2;
			test_string="3D 5D ?? ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);

			// Add another card
			detect::BaseCard card3(12,17);
			hand.addToHand(card3);
			test_hand[2]=card3;
			test_string="3D 5D QH ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);

			// Try to add a card thats already in the hand
			detect::BaseCard card4(12,17);
			hand.addToHand(card4);
			test_string="3D 5D QH ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);

			// Add two more cards
			detect::BaseCard card5(8,18);
			detect::BaseCard card6(10,16);
			hand.addToHand(card5);
			hand.addToHand(card6);
			test_hand[3]=card5;
			test_hand[4]=card6;
			test_string="3D 5D QH 8S 0C ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);

			// Check sorts		
			std::string sorted_hand="QH 0C 8S 5D 3D ?? ?? \n";
			hand.sort();
			EXPECT_EQ(hand.print().str(),sorted_hand);

	}

	GTEST_TEST(TestPoker, TestDeck)
	{	
		poker::Hand robot_hand;

		// add cards to hand
		robot_hand.addToHand(detect::BaseCard(3,18));
		robot_hand.addToHand(detect::BaseCard(11,16));

		poker::Deck deck(robot_hand);

		// Does Deck initialization work
		for(const detect::BaseCard& card: deck.deck_)
		{
			EXPECT_NE(card, robot_hand.hand_.at(0));
			EXPECT_NE(card, robot_hand.hand_.at(1));
		}

		EXPECT_EQ(deck.deck_.size(),50);

		// does pull a card work
		EXPECT_EQ(deck.pullCard(), deck.deck_.at(0));

		// is pos_tracker incrementen by pullCard?
		EXPECT_EQ(deck.getPosition(),1);

		// is pos_tracker incremented by burnCard?
		deck.burnCard();
		EXPECT_EQ(deck.getPosition(),2);

		// check pull card again to make sure
		EXPECT_EQ(deck.pullCard(), deck.deck_.at(2));
	}

	GTEST_TEST(TestPoker, TestHandBuilder)
	{
		std::string robot_hand_string = "QH 0C 8S 5D 3D ?? ?? \n";
		std::string player_hand_string = "QH 0C 8S ?? ?? ?? ?? \n";

		poker::Hand robot_hand{};
		std::vector<poker::Hand> player_hands{};
		player_hands.resize(1);

		std::vector<detect::BaseCard> robot_cards{
			detect::BaseCard(detect::FIVE, detect::DIAMONDS),
			detect::BaseCard(detect::THREE, detect::DIAMONDS)
			};	

		std::vector<detect::BaseCard> public_cards{
			detect::BaseCard(detect::QUEEN, detect::HEARTS),
			detect::BaseCard(detect::TEN, detect::CLUBS),
			detect::BaseCard(detect::EIGHT, detect::SPADES),
		};

		poker::HandBuilder::buildHands(
			public_cards,
			robot_cards,
			player_hands,
			robot_hand
		);

		player_hands.at(0).sort();
		robot_hand.sort();

		EXPECT_EQ(player_hands.at(0).print().str(), player_hand_string);
		EXPECT_EQ(robot_hand.print().str(), robot_hand_string);
	}

	GTEST_TEST(TestPoker,TestGetRanking)
	{
		fs::path filename = fs::current_path() / "unit_tests" / "utilities" / "PokerHands" / "Rankings.txt";
		std::ifstream file;
		file.open(filename.string());	
		std::string line;
		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				std::vector<std::string> cont = split(line, ';');
				int ranking = std::stoi(cont.at(1));
				poker::Hand hand=convertToHand(cont.at(0));
				poker::RankDeterminator get_ranking;
				get_ranking.run(hand);
				EXPECT_EQ(get_ranking.getRanking(), ranking);
			}
			file.close();
		}
		else
		{
			std::cerr << "Could not open file" << std::endl;
		}

	}

	GTEST_TEST(TestPoker,TestGetWinner)
	{

		fs::path filename = fs::current_path() / "unit_tests" / "utilities" / "PokerHands" / "CompetingHands.txt";
		std::ifstream file;

		// Read player hands from file
		file.open(filename.string());	
		std::string line;
		int nr_of_players{0};

		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				std::vector<std::string> cont = split(line, ';');
				nr_of_players = std::stoi(cont.at(0));
				int winner = std::stoi(cont.at(1));
				poker::Hand robot_hand = convertToHand(cont.at(2));
				std::vector<poker::Hand> player_hands{};
							
				for(int i=3; i<cont.size()-1; ++i) 
				{
					player_hands.emplace_back(convertToHand(cont.at(i)));
				}

				int det_winner = poker::WinnerDeterminator::determineWinner(player_hands, robot_hand);

				EXPECT_EQ(det_winner, winner);
			}
			file.close();
		}
		else
		{
			std::cerr << "Could not open file" << std::endl;
		}

	}

	// Calculated probability of winning with starting hand given in txt file and compares to expected value
	GTEST_TEST(TestPoker,TestSimulationRun)
	{
		// Set Up DataStructures
		poker::SimSettings settings{};
		settings.nr_of_simulation_runs = 100000;
		detect::DataDetect detected_cards{};

		fs::path filename = fs::current_path() / "unit_tests" / "utilities" / "PokerHands" / "StartingHands.txt";
		std::ifstream file;

		double expected_probability{};
		// Read player hands from file
		file.open(filename.string());	
		std::string line;
		
		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				poker::Simulation sim(settings, detected_cards, false);
				std::vector<std::string> cont = split(line, ';');
				settings.nr_of_human_players = std::stoi(cont.at(0));
				expected_probability = std::stod(cont.at(1));

				// add cards to robot starting hand
				std::vector<std::string> cards = split(cont.at(2)); 
				detect::Mapping mapping;

				// Convert string to cards and add cards to hand
				for(int i = 0; i < cards.size(); ++i)
				{
					detected_cards.robot_cards.emplace_back(convertToCard(cards.at(i)));
				}

				sim.run();
				std::pair<double,double> prob = sim.data_.probability;
				std::cout << prob.first << ", " << prob.second << std::endl;
				EXPECT_TRUE((prob.first >= expected_probability-1) && (prob.first <= expected_probability+1));
				detected_cards.robot_cards.clear();
			}
			file.close();
		}
		else
		{
			std::cout << "Could not open file" << std::endl;
		}

	}

} // end namespace unit test