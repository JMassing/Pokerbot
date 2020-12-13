#include <gtest/gtest.h>

#include "MoneyTracker.hpp"
#include "DataPoker.hpp"

namespace UnitTest
{
    // Test MoneyTracker
    GTEST_TEST(Test_MoneyTracker, processBet_adds_player_bet_to_money_in_play)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money_in_play=400; data.players.at(0).current_bet=200; 
        data.players.at(1).money_in_play=1400; data.players.at(1).current_bet=100; 
        data.players.at(2).money_in_play=700; data.players.at(2).current_bet=0; 
        money_tracker.processBet();
        EXPECT_EQ(data.players.at(0).money_in_play, 600);
        EXPECT_EQ(data.players.at(1).money_in_play, 1500);
        EXPECT_EQ(data.players.at(2).money_in_play, 700);
    }

    GTEST_TEST(Test_MoneyTracker, processBet_resets_player_bets)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money_in_play=400; data.players.at(0).current_bet=200; 
        data.players.at(1).money_in_play=1400; data.players.at(0).current_bet=100; 
        data.players.at(2).money_in_play=700; data.players.at(2).current_bet=0; 
        money_tracker.processBet();
        EXPECT_EQ(data.players.at(0).current_bet, 0);
        EXPECT_EQ(data.players.at(1).current_bet, 0);
        EXPECT_EQ(data.players.at(2).current_bet, 0);
    }

    GTEST_TEST(Test_MoneyTracker, calcPotSize_adds_all_money_in_play_to_pot)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money_in_play=400;  
        data.players.at(1).money_in_play=1400;  
        data.players.at(2).money_in_play=700;
        money_tracker.calcPotSize();
        EXPECT_EQ(data.pot_size, 2500);
    }

    GTEST_TEST(Test_MoneyTracker, hasPlayerLessThanBigblind_returns_false_if_all_players_have_more_money_than_bigblind)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money=400;  
        data.players.at(1).money=1400;  
        data.players.at(2).money=700;
        EXPECT_FALSE(money_tracker.hasPlayerLessThanBigblind(100));
    }

    GTEST_TEST(Test_MoneyTracker, hasPlayerLessThanBigblind_returns_true_if_one_player_has_less_money_than_bigblind)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money=400;  
        data.players.at(1).money=1400;  
        data.players.at(2).money=700;
        EXPECT_TRUE(money_tracker.hasPlayerLessThanBigblind(600));
    }

    GTEST_TEST(Test_MoneyTracker, isPlayerAllIn_returns_true_if_one_player_is_all_in)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money=-100;  
        data.players.at(1).money=1400;  
        data.players.at(2).money=700;
        EXPECT_TRUE(money_tracker.isPlayerAllIn());
    }

    GTEST_TEST(Test_MoneyTracker, isPlayerAllIn_returns_true_if_one_player_has_negative_money)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money=-100;  
        data.players.at(1).money=1400;  
        data.players.at(2).money=700;
        EXPECT_TRUE(money_tracker.isPlayerAllIn());
    }  
   
    GTEST_TEST(Test_MoneyTracker, isPlayerAllIn_returns_false_if_no_player_is_all_in)
    {
        poker::DataPoker data;
        poker::MoneyTracker money_tracker(data);
        data.players.resize(3);
        data.players.at(0).money=500;  
        data.players.at(1).money=1400;  
        data.players.at(2).money=700;
        EXPECT_FALSE(money_tracker.isPlayerAllIn());
    }
} //end namespace UnitTest