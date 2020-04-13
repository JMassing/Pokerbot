#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>

#include "../poker/include/Hand.h"
#include "../poker/include/Deck.h"
#include "../poker/include/Simulation.h"
#include "../poker/include/GetRanking.h"

#include "utilities/HelperClasses/SimulationInternal.h"

#include "../detection/include/Card.h"
#include "../detection/include/Mapping.h"

namespace UnitTest{

	// Split string_hand
	std::vector<std::string> split(std::string line, char delim=' ')
	{ 
		std::size_t current, previous = 0;
		std::vector<std::string> cont;
		current = line.find(delim);
		while (current != std::string::npos) {
			cont.push_back(line.substr(previous, current - previous));
			previous = current + 1;
			current = line.find(delim, previous);
		}
		cont.push_back(line.substr(previous, current - previous));
		return cont;
	}

	// Converts String read from file to class hand. Examplary String: 3S 9D AS JC 4D 9H 10H
	poker::Hand convertToHand(std::string string_hand)
	{
		poker::Hand hand;
		detect::Mapping mapping;
		std::vector<std::string> cont = split(string_hand); 
		
		// Convert string to cards and add cards to hand
		for(const auto& card: cont)
		{
			std::string rank(1, card.at(0) );
			std::string suit(1, card.at(1) );
			detect::Card tmp(mapping.text_mappings.left.at(rank), mapping.text_mappings.left.at(suit) );
			hand.addToHand(tmp);
		}
		return hand;
	}

	TEST(TestPoker,TestHand)
	{
			poker::Hand hand;
			// Test initialization of hand
			std::string test_string{"?? ?? ?? ?? ?? ?? ?? \n"};
			std::array<detect::Card,7> test_hand;
			test_hand.fill(detect::Card());
			ASSERT_EQ(hand.print().str(), test_string);
			ASSERT_EQ(hand.hand_, test_hand);
			// Add a card
			detect::Card card1(3,15);
			hand.addToHand(card1);
			test_hand[0]=card1;
			test_string="3D ?? ?? ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);
			// Add another card
			detect::Card card2(5,15);
			hand.addToHand(card2);
			test_hand[1]=card2;
			test_string="3D 5D ?? ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);
			// Add another card
			detect::Card card3(12,17);
			hand.addToHand(card3);
			test_hand[2]=card3;
			test_string="3D 5D QH ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);
			// Try to add a card thats already in the hand
			detect::Card card4(12,17);
			hand.addToHand(card4);
			test_string="3D 5D QH ?? ?? ?? ?? \n";
			EXPECT_EQ(hand.print().str(), test_string);
			EXPECT_EQ(hand.hand_, test_hand);
			// Add two more cards
			detect::Card card5(8,18);
			detect::Card card6(10,16);
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

	TEST(TestPoker,TestDeck)
	{	
		poker::Hand robot_hand;
		// add cards to hand
		robot_hand.addToHand(detect::Card(3,18));
		robot_hand.addToHand(detect::Card(11,16));

		poker::Deck deck(robot_hand);
		// Does Deck initialization work
		for(const detect::Card& card: deck.deck_)
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
		EXPECT_EQ(deck.pullCard(), deck.deck_[2]);
	}

	TEST(TestPoker,TestGetRanking)
	{
		std::ifstream file;
		file.open("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\unit_tests\\utilities\\PokerHands\\Rankings.txt");	
		std::string line;
		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				std::vector<std::string> cont = split(line, ';');
				int ranking = std::stoi(cont.at(1));
				poker::Hand hand=convertToHand(cont.at(0));
				poker::GetRanking get_ranking;
				get_ranking.run(hand);
				EXPECT_EQ(get_ranking.getRanking(), ranking);
			}
			file.close();
		}
		else
		{
			std::cout << "Could not open file" << std::endl;
		}

	}

	TEST(TestPoker,TestSimulationGetWinner)
	{
		std::ifstream file;
		// Read player hands from file
		file.open("C:\\Users\\julim\\Desktop\\Projects\\Pokerbot\\unit_tests\\utilities\\PokerHands\\CompetingHands.txt");	
		std::string line;
		int nr_of_players{0};
		if(file.is_open())
		{
			while(std::getline(file, line))
			{
				std::vector<std::string> cont = split(line, ';');
				nr_of_players=std::stoi(cont.at(0));
				int winner=std::stoi(cont.at(1));
				SimulationInternal sim(nr_of_players);
				sim.setRobotHand(convertToHand(cont.at(2)));
				int k=0;				
				for(int i=3; i<cont.size()-1; ++i) 
				{
					sim.setPlayerHands(convertToHand(cont.at(i)),k);
					++k;
				}
				
				EXPECT_EQ(sim.getWinner(), winner);
			}
			file.close();
		}
		else
		{
			std::cout << "Could not open file" << std::endl;
		}

	}

} // end namespace unit test