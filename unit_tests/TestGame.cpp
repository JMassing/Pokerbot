#include <gtest/gtest.h>
#include <memory>
#include <iostream>

#include "DataPoker.hpp"
#include "Game.hpp"
#include "Poker_Mocks.hpp"
#include "Player.hpp"
#include "DataDetect.hpp"

namespace UnitTest
{
	using ::testing::AtLeast;
	using ::testing::Return;
	using ::testing::_;
	using ::testing::NiceMock;

	GTEST_TEST(TestGame, play_checkUserInput_if_gui_interface_connected)
	{
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1);
		poker::GameSettings settings{};
		poker::Game game(settings);
		game.attachGuiInterface(mock_gui_if);		
		game.play();
	}

	GTEST_TEST(TestGame, play_calls_getSettings_on_user_input)
	{
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(true));
		EXPECT_CALL(*mock_gui_if, getSettings()).Times(1);
		poker::GameSettings settings{};
		poker::Game game(settings);
		game.attachGuiInterface(mock_gui_if);		
		game.play();
	}

	GTEST_TEST(TestGame, play_calls_getData_from_gui_interface_once)
	{
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, getData()).Times(1);
		poker::GameSettings settings{};
		poker::Game game(settings);
		game.attachGuiInterface(mock_gui_if);		
		game.play();
	}

	GTEST_TEST(TestGame, play_setData_if_gui_interface_connected)
	{
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, setData(_)).Times(1);
		poker::GameSettings settings{};
		poker::Game game(settings);
		game.attachGuiInterface(mock_gui_if);		
		game.play();
	}

	GTEST_TEST(TestGame, play_setSettings_if_gui_interface_connected)
	{
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, setSettings(_)).Times(1);
		poker::GameSettings settings{};
		poker::Game game(settings);
		game.attachGuiInterface(mock_gui_if);		
		game.play();
	}

	GTEST_TEST(TestGame, play_call_start_on_start)
	{
		poker::GameSettings settings{}; settings.start_game = true; settings.nr_of_human_players = 1;
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(true));
		EXPECT_CALL(*mock_gui_if, getSettings()).WillOnce(Return(settings));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);	
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		EXPECT_CALL(*mock_controller, start()).Times(1);
		game.mockController(std::move(mock_controller));				
		game.play();
	}

	GTEST_TEST(TestGame, play_will_call_stop_on_stop)
	{
		poker::GameSettings settings{}; settings.stop_game= true; settings.nr_of_human_players = 1;
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(true));
		EXPECT_CALL(*mock_gui_if, getSettings()).WillOnce(Return(settings));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		EXPECT_CALL(*mock_controller, stop()).Times(1);
		game.mockController(std::move(mock_controller));		
		game.play();
	}

	GTEST_TEST(TestGame, play_will_call_stop_if_player_has_no_money)
	{
		// set up required game state for tests
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.players.at(1).money = 10;
		gui_data.game_phase = poker::HAND_CARDS;
		// Mocks
 		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();
		EXPECT_CALL(*mock_controller, stop()).Times(1);
		// Game Class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);		
		game.mockController(std::move(mock_controller));	
		game.play();
	}

	GTEST_TEST(TestGame, play_will_call_setGamephase_when_playing)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(9,15));
		data_detect.cards.emplace_back(BaseCard(5,16));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::HAND_CARDS;
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillOnce(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		EXPECT_CALL(*mock_controller, setGamePhase()).Times(1);
		// Game Class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		game.play();
	}

	GTEST_TEST(TestGame, play_will_skip_player_if_folded)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(9,15));
		data_detect.cards.emplace_back(BaseCard(5,16));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::HAND_CARDS; gui_data.whos_turn = 0; 
		gui_data.players.at(0).has_folded = true;
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillOnce(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();
		// Game Class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);	
		game.mockController(std::move(mock_controller));	
		game.play();
		EXPECT_EQ(game.data_.whos_turn, 1);
	}

	GTEST_TEST(TestGame, play_will_set_player_decision_to_check_and_advance_next_round)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(9,15));
		data_detect.cards.emplace_back(BaseCard(5,16));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::BET_HAND; gui_data.whos_turn = 0; 
		gui_data.players.at(0).current_decision = poker::HAS_RAISED;
		gui_data.highest_bet = 1000; gui_data.players.at(0).money_bet_in_phase = gui_data.highest_bet;
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillOnce(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		// Set Up game class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		game.play();
		EXPECT_EQ(game.data_.players.at(0).current_decision, poker::CHECK);
	}

	GTEST_TEST(TestGame, play_proceed_to_next_phase_if_player_all_in_and_all_called)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(9,15));
		data_detect.cards.emplace_back(BaseCard(5,16));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::BET_HAND; gui_data.whos_turn = 0; 
		gui_data.players.at(0).is_all_in = true; gui_data.players.at(1).current_decision = poker::CALL;
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillOnce(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		// Set Up game class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		game.play();
		EXPECT_EQ(game.data_.game_phase, poker::FLOP);
	}

	GTEST_TEST(TestGame, play_with_four_aces_robot_should_raise_on_his_turn)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(14,17));
		data_detect.cards.emplace_back(BaseCard(14,18));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::HAND_CARDS; gui_data.whos_turn = 0; 
		poker::DataPoker gui_data2{};
		gui_data2.players.resize(2, poker::Player(10000));
		gui_data2.game_phase = poker::BET_HAND; gui_data2.whos_turn = 0; 
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(2).WillRepeatedly(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).Times(2).WillOnce(Return(gui_data)).WillOnce(Return(gui_data2));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).Times(2).WillRepeatedly(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		// Set Up game class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		// first play to set robot cards, second play to test
		game.play();
		game.play();
		EXPECT_EQ(game.data_.players.at(0).current_decision, poker::HAS_RAISED);
		EXPECT_EQ(game.data_.whos_turn, 1);
	}

	GTEST_TEST(TestGame, play_call_next_phase_if_all_players_called)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(9,15));
		data_detect.cards.emplace_back(BaseCard(5,16));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::BET_HAND; gui_data.whos_turn = 0; 
		gui_data.players.at(0).current_decision = poker::CALL; gui_data.players.at(1).current_decision = poker::CALL;
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillOnce(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		EXPECT_CALL(*mock_controller, resetPhase()).Times(1);
		// Set Up game class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		game.play();
		EXPECT_EQ(game.data_.game_phase, poker::FLOP);
	}

	GTEST_TEST(TestGame, play_gets_winner_if_all_players_have_folded)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		data_detect.cards.emplace_back(BaseCard(9,15));
		data_detect.cards.emplace_back(BaseCard(5,16));
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::BET_HAND; gui_data.whos_turn = 0; 
		gui_data.players.at(0).current_decision = poker::FOLD; 
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillOnce(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		// Set Up game class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		game.play();
		EXPECT_EQ(game.data_.winner, 1);
	}

	GTEST_TEST(TestGame, play_starts_next_round_on_user_input)
	{
		// set up required game state for tests
		detect::DataDetect data_detect{};
		poker::DataPoker gui_data{};
		gui_data.players.resize(2, poker::Player(10000));
		gui_data.game_phase = poker::BET_HAND; gui_data.whos_turn = 0; 
		gui_data.next_round = true;
		// mocks
		std::shared_ptr<NiceMock<MockPokerGuiInterface>> mock_gui_if =
			std::make_shared<NiceMock<MockPokerGuiInterface>>();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1).WillOnce(Return(false));
		EXPECT_CALL(*mock_gui_if, getData()).WillOnce(Return(gui_data));
		std::shared_ptr<NiceMock<MockPokerDetectInterface>> mock_detect_if =
			std::make_shared<NiceMock<MockPokerDetectInterface>>();
		EXPECT_CALL(*mock_detect_if, getData()).WillRepeatedly(Return(data_detect));
		std::unique_ptr<NiceMock<MockController>> mock_controller = 
			std::make_unique<NiceMock<MockController>>();	
		EXPECT_CALL(*mock_controller, startNextRound()).Times(1);
		// Set Up game class
		poker::GameSettings initial_settings{};
		GameTester game(initial_settings);
		game.attachGuiInterface(mock_gui_if);	
		game.attachDetectInterface(mock_detect_if);
		game.mockController(std::move(mock_controller));	
		game.play();
	}

} // end namespace unit test