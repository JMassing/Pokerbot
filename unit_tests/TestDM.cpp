#include <boost/filesystem.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <utility>

#include "DecisionMaker.hpp"
#include "DataPoker.hpp"

namespace fs = boost::filesystem;

namespace UnitTest
{
	namespace{
		//sets values in data to standard values used in most tests
		void init_data(poker::DataPoker& data)
		{
			data.players.resize(2);
			data.highest_bet = 100;
			data.pot_size = 200;
			data.players.at(0).money = 10000;
		}
	}
	GTEST_TEST(TestDM, WhenProbabilitybelow40FoldOnRaise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 39;				
		data.players.at(0).money_bet_in_phase = 50;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::FOLD);
	}

	GTEST_TEST(TestDM, WhenProbabilitybelow40CheckOnNoRaise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 39;
		data.players.at(0).money_bet_in_phase = 100;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::CHECK);
	}

	GTEST_TEST(TestDM, WhenProbability40to60FoldOnHighRaise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 50;
		data.highest_bet = 600;
		data.players.at(0).money_bet_in_phase = 0;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::FOLD);		
	}

	GTEST_TEST(TestDM, WhenProbability40to60CallOnLowRaise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 50;
		data.highest_bet = 200;
		data.players.at(0).money_bet_in_phase = 100;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::CALL);	
		EXPECT_EQ(data.players.at(0).current_bet, 100);	
	}

	GTEST_TEST(TestDM, WhenProbability40to60CheckOnNoRaise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 50;
		data.highest_bet = 400;
		data.players.at(0).money_bet_in_phase = 400;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::CHECK);		
	}

	GTEST_TEST(TestDM, WhenProbability60to80Raise3TimesBigBlind)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};

		data.probability.first = 65;
		data.players.at(0).money_bet_in_phase = 0;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::HAS_RAISED);
		EXPECT_EQ(data.players.at(0).current_bet, 300);
		EXPECT_EQ(data.highest_bet, 300);		
	}

	GTEST_TEST(TestDM, WhenProbability60to80CallOnHighRaise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 65;
		data.highest_bet = 1000;
		data.players.at(0).money_bet_in_phase = 400;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::CALL);		
		EXPECT_EQ(data.players.at(0).current_bet, 600);
		EXPECT_EQ(data.highest_bet, 1000);		
	}

	GTEST_TEST(TestDM, WhenProbabilityAbove80Raise)
	{
		poker::DataPoker data;
		init_data(data);
		poker::DecisionMaker dm{data};
		data.probability.first = 85;
		data.highest_bet = 1000;
		data.players.at(0).money_bet_in_phase = 400;
		dm.makeDecision();
		EXPECT_EQ(data.players.at(0).current_decision, poker::HAS_RAISED);		
		EXPECT_EQ(data.players.at(0).current_bet, 2000);
		EXPECT_EQ(data.highest_bet, 2400);		
	}


} // end namespace unit test