#include <gtest/gtest.h>

#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <utility>

#include "Hand.hpp"
#include "Deck.hpp"
#include "BaseCard.hpp"
#include "Player.hpp"
#include "HelperFunctions.hpp"
#include "HandBuilder.hpp"

namespace UnitTest
{
	//Test Hand
	GTEST_TEST(Test_Hand, constructor_initilizes_correctly)
	{
		poker::Hand hand;
		std::array<BaseCard,7> expected_hand;
		expected_hand.fill(BaseCard());
		EXPECT_EQ(hand.cards_, expected_hand);
	}

	GTEST_TEST(Test_Hand, addToHand_adds_new_cards)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(7,18);
		hand.addToHand(card1);
		hand.addToHand(card2);
		std::array<BaseCard,7> expected_hand;
		expected_hand.fill(BaseCard());
		expected_hand.at(0) = card1;
		expected_hand.at(1) = card2;
		EXPECT_EQ(hand.cards_, expected_hand);
	}

	GTEST_TEST(Test_Hand, addToHand_does_not_add_known_cards)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(7,18);
		// Add once
		hand.addToHand(card1);
		hand.addToHand(card2);
		// Try to add again
		hand.addToHand(card1);
		hand.addToHand(card2);
		std::array<BaseCard,7> expected_hand;
		expected_hand.fill(BaseCard());
		expected_hand.at(0) = card1;
		expected_hand.at(1) = card2;
		EXPECT_EQ(hand.cards_, expected_hand);
	}

	GTEST_TEST(Test_Hand, print_prints_expected_format)
	{
		poker::Hand hand;
		std::string expected_string{"3D 7S ?? ?? ?? ?? ?? \n"};
		hand.addToHand(BaseCard(3,15));
		hand.addToHand(BaseCard(7,18));
		EXPECT_EQ(hand.print().str(), expected_string);
	}

	GTEST_TEST(Test_Hand, containsCard_returns_true_if_card_in_hand)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(7,18);
		// Add once
		hand.addToHand(card1);
		EXPECT_TRUE(hand.containsCard(card1));
	}

	GTEST_TEST(Test_Hand, containsCard_returns_false_if_card_not_in_hand)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(7,18);
		// Add once
		hand.addToHand(card1);
		EXPECT_FALSE(hand.containsCard(card2));
	}

	GTEST_TEST(Test_Hand, containsRank_returns_true_if_rank_in_hand)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(7,18);
		// Add once
		hand.addToHand(card1);
		EXPECT_TRUE(hand.containsRank(BaseCard(3,16).rank));
	}

	GTEST_TEST(Test_Hand, containsRank_returns_false_if_rank_not_in_hand)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(7,15);
		// Add once
		hand.addToHand(card1);
		EXPECT_FALSE(hand.containsRank(card2.rank));
	}

	GTEST_TEST(Test_Hand, containsSuit_returns_true_if_suit_in_hand)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(3,18);
		// Add once
		hand.addToHand(card1);
		EXPECT_TRUE(hand.containsSuit(BaseCard(10,15).suit));
	}

	GTEST_TEST(Test_Hand, containsSuit_returns_false_if_suit_not_in_hand)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(3,18);
		// Add once
		hand.addToHand(card1);
		EXPECT_FALSE(hand.containsSuit(card2.suit));
	}

	GTEST_TEST(Test_Hand, sort_sorts_hand_ascending_by_rank)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(3,18);
		BaseCard card3 = BaseCard(4,17);
		BaseCard card4 = BaseCard(9,18);
		BaseCard card5 = BaseCard(11,15);
		BaseCard card6 = BaseCard(11,16);
		BaseCard card7 = BaseCard(5,18);
		hand.addToHand(card1);
		hand.addToHand(card2);
		hand.addToHand(card3);
		hand.addToHand(card4);
		hand.addToHand(card5);
		hand.addToHand(card6);
		hand.addToHand(card7);
		hand.sort();
		std::array<BaseCard,7> expected_hand{card6, card5, card4, card7, card3, card2, card1};
		EXPECT_EQ(hand.cards_, expected_hand);
	}

	GTEST_TEST(Test_Hand, reset_resets_hand_to_unknown)
	{
		poker::Hand hand;
		BaseCard card1 = BaseCard(3,15);
		BaseCard card2 = BaseCard(3,18);
		BaseCard card3 = BaseCard(4,17);
		BaseCard card4 = BaseCard(9,18);
		BaseCard card5 = BaseCard(11,15);
		BaseCard card6 = BaseCard(11,16);
		BaseCard card7 = BaseCard(5,18);
		hand.addToHand(card1);
		hand.addToHand(card2);
		hand.addToHand(card3);
		hand.addToHand(card4);
		hand.addToHand(card5);
		hand.addToHand(card6);
		hand.addToHand(card7);
		hand.reset();
		std::array<BaseCard,7> expected_hand{};
		EXPECT_EQ(hand.cards_, expected_hand);
	}
	
	// Test Deck
	GTEST_TEST(TesT_Deck, constructor_initializes_correctly)
	{
		poker::Hand robot_hand;
		//deal cards to robot
		robot_hand.addToHand(BaseCard(3,18));
		robot_hand.addToHand(BaseCard(11,16));
		poker::Deck deck(robot_hand);
		//Dealt Cards are not part of the deck
		for(const BaseCard& card: deck.deck_)
		{
			EXPECT_NE(card, robot_hand.cards_.at(0));
			EXPECT_NE(card, robot_hand.cards_.at(1));
		}
		EXPECT_EQ(deck.deck_.size(), 50);
	}

	GTEST_TEST(Test_deck, pull_card_pulls_first_card)
	{
		poker::Hand robot_hand;
		//deal cards to robot
		robot_hand.addToHand(BaseCard(3,18));
		robot_hand.addToHand(BaseCard(11,16));
		poker::Deck deck(robot_hand);
		EXPECT_EQ(deck.pullCard(), deck.deck_.at(0));
	}
	
	GTEST_TEST(Test_deck, pull_card_increments_pos_tracker)
	{
		poker::Hand robot_hand;
		//deal cards to robot
		robot_hand.addToHand(BaseCard(3,18));
		robot_hand.addToHand(BaseCard(11,16));
		poker::Deck deck(robot_hand);
		deck.pullCard();
		deck.pullCard();
		deck.pullCard();
		EXPECT_EQ(deck.getPosition(),3);
	}

	//Test Hand Builder

	GTEST_TEST(Test_HandBuilder, buildHands_assigns_cards_correctly)
	{
		std::string robot_hand_string = "QH 0C 8S 5D 3D ?? ?? \n";
		std::string player_hand_string = "QH 0C 8S ?? ?? ?? ?? \n";

		std::vector<poker::Player> players{};
		players.resize(2);

		std::vector<BaseCard> robot_cards{
			BaseCard(FIVE, DIAMONDS),
			BaseCard(THREE, DIAMONDS)
			};	

		std::vector<BaseCard> public_cards{
			BaseCard(QUEEN, HEARTS),
			BaseCard(TEN, CLUBS),
			BaseCard(EIGHT, SPADES),
		};

		poker::HandBuilder::buildHands(
			public_cards,
			robot_cards,
			players
		);

		for(auto& player : players)
		{
			player.hand.sort();
		}

		EXPECT_EQ(players.at(1).hand.print().str(), player_hand_string);
		EXPECT_EQ(players.at(0).hand.print().str(), robot_hand_string);
	}

} // end namespace unit test