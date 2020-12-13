#include <boost/filesystem.hpp>
#include <boost/dll.hpp>
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
#include "Player.hpp"
#include "MonteCarlo.hpp"
#include "HelperFunctions.hpp"
#include "WinnerDeterminator.hpp"
#include "HandBuilder.hpp"
#include "GameSettings.hpp"
#include "DataPoker.hpp"

namespace fs = boost::filesystem;

namespace UnitTest
{
	// Check if hand ranks are determined correctly
	GTEST_TEST(Test_RankDeterminator, getRanking_returns_the_right_ranks)
	{
		// Read hands and corresponding ranks from file
		fs::path filename = boost::dll::program_location().parent_path() / "unit_tests" / "utilities" / "PokerHands" / "Rankings.txt";
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
				// Check if rank is correct
				EXPECT_EQ(get_ranking.getRanking(), ranking);
			}
			file.close();
		}
		else
		{
			std::cerr << "Could not open file" << std::endl;
		}

	}

	// Check if hand winners are determined correctly
	GTEST_TEST(Test_WinnerDeterminator, getWinner_returns_correct_winner)
	{
		// Read hands and corresponding winners from file
		fs::path filename = boost::dll::program_location().parent_path() / "unit_tests" / "utilities" / "PokerHands" / "CompetingHands.txt";
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
	// Expected values taken from https://wizardofodds.com/games/texas-hold-em/6-player-game/. 
	GTEST_TEST(TestPoker, TestMonteCarlo)
	{
		// Set Up DataStructures
		int iterations = 100000;

		fs::path filename = boost::dll::program_location().parent_path() / "unit_tests" / "utilities" / "PokerHands" / "StartingHands.txt";
		std::ifstream file;

		double expected_probability{};
		// Read player hands from file
		file.open(filename.string());	
		std::string line;

		if(file.is_open())
		{
			while(std::getline(file, line))
			{	
				poker::DataPoker data{};
				std::vector<BaseCard> robot_cards{};
				std::vector<BaseCard> public_cards{};
				std::vector<std::string> cont = split(line, ';');
				int nr_of_players = std::stoi(cont.at(0));
				expected_probability = std::stod(cont.at(1));
				// add cards to robot starting hand
				std::vector<std::string> cards = split(cont.at(2)); 
				Mapping mapping;

				// Convert string to cards and add cards to hand
				for(int i = 0; i < cards.size(); ++i)
				{
					robot_cards.emplace_back(convertToCard(cards.at(i)));
				}

				data.players.resize(nr_of_players);
				poker::HandBuilder::buildHands(public_cards, robot_cards, data.players);
				// Run simulation
				std::pair<double,double> prob = 
					poker::MonteCarlo::run(
						iterations, 
						poker::Deck(data.players.at(0).hand), 
						data.players,
						poker::HAND_CARDS,
						false
						);

				std::cout << prob.first << ", " << prob.second << std::endl;
				EXPECT_TRUE( (prob.first  >= expected_probability-1) && 
							 (prob.first  <= expected_probability+1)
							);
			}
			file.close();
		}
		else
		{
			std::cout << "Could not open file" << std::endl;
		}

	}

} // end namespace unit test