#include <gtest/gtest.h>

#include "MoneyTracker.hpp"
#include "DataPoker.hpp"
#include "DecisionProcessor.hpp"
#include "Player.hpp"
#include "GameStateController.hpp"
#include "GameSettings.hpp"
#include "BaseCard.hpp"

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

    //Test DecisionProcessor
    GTEST_TEST(Test_DecisionProcessor, haveAllPlayersDecided_returns_false_if_one_player_has_not_decided)
    {
        poker::DataPoker data;
        poker::DecisionProcessor decision_processor(data);
        data.players.resize(3);
        data.players.at(0).current_decision=poker::RAISE;  
        data.players.at(1).current_decision=poker::RAISE; 
        data.players.at(2).current_decision=poker::NO_DECISION; 
        EXPECT_FALSE(decision_processor.haveAllPlayersDecided());
    }

    //Test DecisionProcessor
    GTEST_TEST(Test_DecisionProcessor, haveAllPlayersDecided_returns_true_if_all_players_decided)
    {
        poker::DataPoker data;
        poker::DecisionProcessor decision_processor(data);
        data.players.resize(3);
        data.players.at(0).current_decision=poker::RAISE;  
        data.players.at(1).current_decision=poker::RAISE; 
        data.players.at(2).current_decision=poker::CHECK; 
        EXPECT_TRUE(decision_processor.haveAllPlayersDecided());
    }

    GTEST_TEST(Test_DecisionProcessor, wasRaised_returns_true_if_robot_raised)
    {
        poker::DataPoker data;
        poker::DecisionProcessor decision_processor(data);
        data.players.resize(2);
        data.players.at(0).current_decision=poker::RAISE;  
        data.players.at(1).current_decision=poker::CHECK; 
        EXPECT_TRUE(decision_processor.wasRaised());
        data.players.at(0).current_decision=poker::HAS_RAISED;  
        data.players.at(1).current_decision=poker::CHECK; 
        EXPECT_TRUE(decision_processor.wasRaised());
    }

    GTEST_TEST(Test_DecisionProcessor, wasRaised_returns_true_if_player_raised)
    {
        poker::DataPoker data;
        poker::DecisionProcessor decision_processor(data);
        data.players.resize(2);
        data.players.at(0).current_decision=poker::CHECK;  
        data.players.at(1).current_decision=poker::RAISE; 
        EXPECT_TRUE(decision_processor.wasRaised());
        data.players.at(0).current_decision=poker::CHECK;  
        data.players.at(1).current_decision=poker::HAS_RAISED;  
        EXPECT_TRUE(decision_processor.wasRaised());
    }

    GTEST_TEST(Test_DecisionProcessor, wasRaised_returns_false_if_nobody_raised)
    {
        poker::DataPoker data;
        poker::DecisionProcessor decision_processor(data);
        data.players.resize(2);
        data.players.at(0).current_decision=poker::CHECK;  
        data.players.at(1).current_decision=poker::CHECK; 
        EXPECT_FALSE(decision_processor.wasRaised());
    }

    //Test GameStateController
    GTEST_TEST(Test_GameStateController, start_sets_nr_of_players)
    {
        poker::GameSettings settings{};
        poker::DataPoker data{};
        std::vector<BaseCard> robot_cards{};
        std::vector<BaseCard> public_cards{};
        int game_phase = 0;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        settings.nr_of_human_players = 2;
        controller.start();
        EXPECT_EQ(data.players.size(), 3);
    }

    GTEST_TEST(Test_GameStateController, start_sets_button_pos)
    {
        poker::GameSettings settings{};
        poker::DataPoker data{};
        std::vector<BaseCard> robot_cards{};
        std::vector<BaseCard> public_cards{};
        int game_phase = 0;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        settings.nr_of_human_players = 2;
        controller.start();
        EXPECT_TRUE(data.button_pos >= 0 && data.button_pos <= 2);
    }

    GTEST_TEST(Test_GameStateController, start_sets_start_game_false_and_playing_game_true)
    {
        poker::GameSettings settings{};
        poker::DataPoker data{};
        std::vector<BaseCard> robot_cards{};
        std::vector<BaseCard> public_cards{};
        int game_phase = 0;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        settings.nr_of_human_players = 2;
        controller.start();
        EXPECT_TRUE(settings.playing_game);
        EXPECT_FALSE(settings.start_game);
    }

    GTEST_TEST(Test_GameStateController, stop_clears_players_and_cards)
    {
        poker::GameSettings settings{};
        poker::DataPoker data{};
        data.players.resize(3);
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = 0;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        controller.stop();
        EXPECT_EQ(data.players.size(), 0);
        EXPECT_EQ(robot_cards.size(), 0);
        EXPECT_EQ(public_cards.size(), 0);
    }

    GTEST_TEST(Test_GameStateController, stop_resets_game_state)
    {
        poker::GameSettings settings{};
        poker::DataPoker data{};
        data.players.resize(3);
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        controller.stop();
        EXPECT_EQ(data.probability.first, 0);
        EXPECT_EQ(data.probability.second, 0);
        EXPECT_EQ(game_phase, poker::NOT_STARTED);
        EXPECT_EQ(data.highest_bet, 0);
        EXPECT_FALSE(settings.stop_game);
        EXPECT_FALSE(settings.playing_game);
    }

    GTEST_TEST(Test_GameStateController, resetPhase_resets_player_state)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        data.players.at(0).current_decision = poker::CALL; data.players.at(1).current_decision = poker::RAISE;
        data.players.at(0).current_bet = 500; data.players.at(1).current_bet = 700;
        data.players.at(0).money_bet_in_phase = 1000; data.players.at(1).money_bet_in_phase = 1000;
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        data.button_pos = 2;
        controller.resetPhase();
        for(auto& player: data.players)
        {
            EXPECT_EQ(player.current_decision, poker::NO_DECISION);
            EXPECT_EQ(player.current_bet, 0);
            EXPECT_EQ(player.money_bet_in_phase, 0);
        }
        EXPECT_EQ(data.highest_bet, 0);
        EXPECT_EQ(data.whos_turn, 0);
    }

    GTEST_TEST(Test_GameStateController, startNextRound_sets_game_phase_turn_and_button)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        data.button_pos = 2;
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);    
        controller.startNextRound();
        EXPECT_EQ(data.button_pos, 0);    
        EXPECT_EQ(data.whos_turn, 0);
        EXPECT_EQ(game_phase, poker::HAND_CARDS);    
    }

    GTEST_TEST(Test_GameStateController, startNextRound_adds_pot_to_winner)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        data.winner = 2;
        data.pot_size = 1500;
        data.players.at(2).money = 500;   
        data.button_pos = 1; 
        controller.startNextRound();
        EXPECT_EQ(data.players.at(2).money, 2000);
    }

    GTEST_TEST(Test_GameStateController, startNextRound_adds_returns_money_on_tie_and_)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        data.winner = -1;
        data.button_pos = 0;
        data.players.at(0).money = 800; data.players.at(1).money = 300; data.players.at(2).money = 500;    
        data.players.at(0).money_in_play = 500; data.players.at(1).money_in_play = 1000; data.players.at(2).money_in_play = 1000;    
        controller.startNextRound();
        EXPECT_EQ(data.players.at(0).money, 1200);
        EXPECT_EQ(data.players.at(1).money, 1300);
        EXPECT_EQ(data.players.at(2).money, 1450);
    }

    GTEST_TEST(Test_GameStateController, startNextRound_resets_players_and_clears_robot_cards)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        data.winner = -1;
        data.button_pos = 0;
        data.players.at(0).money = 800; data.players.at(1).money = 300; data.players.at(2).money = 500;    
        data.players.at(0).money_in_play = 500; data.players.at(1).money_in_play = 1000; data.players.at(2).money_in_play = 1000;    
        data.players.at(0).has_folded = true;  data.players.at(1).is_all_in = true;
        controller.startNextRound();
        for(auto& player: data.players)
        {
            EXPECT_EQ(player.has_folded, false);
            EXPECT_EQ(player.is_all_in, false);
        }
    }

    GTEST_TEST(Test_GameStateController, startNextRound_resets_robot_cards_winner_and_next_round)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        data.next_round = true;
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        data.winner = 2;
        data.button_pos = 0;
        controller.startNextRound();
        EXPECT_EQ(data.winner, -2);
        EXPECT_EQ(robot_cards.size(), 0);
        EXPECT_EQ(data.next_round, false);
    }

    GTEST_TEST(Test_GameStateController, startNextRound_sets_blinds)
    {
        poker::GameSettings settings{};
        settings.nr_of_human_players = 2;
        poker::DataPoker data{};
        data.players.resize(3);
        data.next_round = true;
        std::vector<BaseCard> robot_cards{BaseCard(2, 15), BaseCard(10, 16)};
        std::vector<BaseCard> public_cards{BaseCard(2, 15), BaseCard(10, 16)};
        int game_phase = poker::BET_HAND;
        poker::GameStateController controller(data, game_phase, settings, robot_cards, public_cards);
        data.winner = 2;
        data.button_pos = 0;
        data.players.at(0).money = 800; data.players.at(1).money = 300; data.players.at(2).money = 500;    
        data.players.at(0).money_in_play = 500; data.players.at(1).money_in_play = 1000; data.players.at(2).money_in_play = 1000;
        controller.startNextRound();
        EXPECT_EQ(data.players.at(0).money_bet_in_phase, settings.big_blind);
        EXPECT_EQ(data.players.at(0).money_in_play, settings.big_blind);
        EXPECT_EQ(data.players.at(0).money, 700);
        EXPECT_EQ(data.players.at(2).money_bet_in_phase, settings.small_blind);
        EXPECT_EQ(data.players.at(2).money_in_play, settings.small_blind);
        EXPECT_EQ(data.players.at(2).money, 450);
    }
} //end namespace UnitTest