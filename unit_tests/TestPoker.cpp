#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "../poker/include/Hand.h"
#include "../poker/include/Deck.h"
#include "../detection/include/Card.h"

TEST(TestPoker,TestHand)
{
		poker::Hand hand;
		// Test initialization of hand
		std::string test_string{"?? ?? ?? ?? ?? \n"};
		std::array<detect::Card,5> test_hand;
		test_hand.fill(detect::Card());
		ASSERT_EQ(hand.print().str(), test_string);
		ASSERT_EQ(hand.hand, test_hand);
		// Add a card
		detect::Card card1(3,15);
		hand.addToHand(card1);
		test_hand[0]=card1;
		test_string="3D ?? ?? ?? ?? \n";
		EXPECT_EQ(hand.print().str(), test_string);
		EXPECT_EQ(hand.hand, test_hand);
		// Add another card
		detect::Card card2(5,15);
		hand.addToHand(card2);
		test_hand[1]=card2;
		test_string="3D 5D ?? ?? ?? \n";
		EXPECT_EQ(hand.print().str(), test_string);
		EXPECT_EQ(hand.hand, test_hand);
		// Add another card
		detect::Card card3(12,17);
		hand.addToHand(card3);
		test_hand[2]=card3;
		test_string="3D 5D QH ?? ?? \n";
		EXPECT_EQ(hand.print().str(), test_string);
		EXPECT_EQ(hand.hand, test_hand);
		// Try to add a card thats already in the hand
		detect::Card card4(12,17);
		hand.addToHand(card4);
		test_string="3D 5D QH ?? ?? \n";
		EXPECT_EQ(hand.print().str(), test_string);
		EXPECT_EQ(hand.hand, test_hand);
		// Add two more cards
		detect::Card card5(8,18);
		detect::Card card6(10,16);
		hand.addToHand(card5);
		hand.addToHand(card6);
		test_hand[3]=card5;
		test_hand[4]=card6;
		test_string="3D 5D QH 8S 10C \n";
		EXPECT_EQ(hand.print().str(), test_string);
		EXPECT_EQ(hand.hand, test_hand);
		// Try to add another card when hand is already full
		detect::Card card7(5,18);
		hand.addToHand(card7);
		EXPECT_EQ(hand.print().str(), test_string);
		EXPECT_EQ(hand.hand, test_hand);
}

TEST(TestPoker,TestDeck)
{	
	std::array<detect::Card,2> robot_hand{detect::Card(5,17), detect::Card(11,16)};
	poker::Deck deck(robot_hand);
	// Does Deck initialization work
	for(const detect::Card& card: deck.deck)
	{
		EXPECT_NE(card, robot_hand[0]);
		EXPECT_NE(card, robot_hand[1]);
	}

	// does pull a card work
	EXPECT_EQ(deck.pullCard(), deck.deck[0]);
	// is pos_tracker incrementen by pullCard?
	EXPECT_EQ(deck.getPosition(),1);
	// is pos_tracker incremented by burnCard?
	deck.burnCard();
	EXPECT_EQ(deck.getPosition(),2);
	// check pull card again to make sure
	EXPECT_EQ(deck.pullCard(), deck.deck[2]);
}