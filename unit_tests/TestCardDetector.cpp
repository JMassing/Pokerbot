#include <memory>
#include <vector>

#include <gtest/gtest.h>
#include <opencv2/core.hpp>

#include "DetectionDataHandler.hpp"
#include "Detect_Mocks.hpp"
#include "ImProcSettings.hpp"
#include "BufferManager.hpp"
#include "Card.hpp"
#include "CardBuffer.hpp"

// Test for PerspectiveCorrector and classes only used by it
namespace UnitTest
{
	using ::testing::AtLeast;
	using ::testing::Return;
	using ::testing::_;
	using ::testing::NiceMock;

	// Test Data Handler
	GTEST_TEST(Test_DataHandler, getProcessingSettings_should_return_false_if_no_interface_detected)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		detect::DetectionDataHandler data_handler{};
		detect::ImProcSettings test_settings{};
		bool result = data_handler.getProcessingSettings(test_settings);
		EXPECT_EQ(result, false);
    };

	GTEST_TEST(Test_DataHandler, getProcessingSettings_should_check_for_user_input)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).Times(1);
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		detect::ImProcSettings test_settings{};
		data_handler.getProcessingSettings(test_settings);
    };

	GTEST_TEST(Test_DataHandler, getProcessingSettings_should_return_false_if_no_user_input)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
		std::make_shared< NiceMock<MockDetectGuiInterface> >();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(false));
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		detect::ImProcSettings test_settings{};
		bool result = data_handler.getProcessingSettings(test_settings);
		EXPECT_EQ(result, false);
    };

	GTEST_TEST(Test_DataHandler, getProcessingSettings_should_return_true_on_user_input)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(true));
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		detect::ImProcSettings test_settings{};
		bool result = data_handler.getProcessingSettings(test_settings);
		EXPECT_EQ(result, true);
    };


	GTEST_TEST(Test_DataHandler, getProcessingSettings_should_set_settings_on_user_input)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		EXPECT_CALL(*mock_gui_if, checkUserInput()).WillOnce(Return(true));
		EXPECT_CALL(*mock_gui_if, getSettings())
			.WillOnce(Return(detect::ImProcSettings(80, 120, 140)));
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		detect::ImProcSettings test_settings{};
		detect::ImProcSettings expected_settings(80, 120, 140);
		data_handler.getProcessingSettings(test_settings);
		EXPECT_EQ(test_settings, expected_settings);
    };

	GTEST_TEST(Test_DataHandler, sendDetectedCards_should_return_false_if_no_gui_if_connected)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		detect::DetectionDataHandler data_handler{};
		std::vector<detect::Card> test_cards{};
		bool result = data_handler.sendDetectedCards(test_cards);
		EXPECT_EQ(result, false);
    };

	GTEST_TEST(Test_DataHandler, sendDetectedCards_should_return_true_if_gui_connected)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		std::vector<detect::Card> test_cards{};
		bool result = data_handler.sendDetectedCards(test_cards);
		EXPECT_EQ(result, true);
    };

	GTEST_TEST(Test_DataHandler, sendDetectedCards_should_send_detected_cards)
	{
		std::vector<detect::Card> test_cards{detect::Card(2, 4), detect::Card(10,2)};
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		EXPECT_CALL(*mock_gui_if, setCards(test_cards)).Times(1);
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		data_handler.sendDetectedCards(test_cards);
    };

	GTEST_TEST(Test_DataHandler, getLiveFrame_should_return_false_if_no_capture_if_connected)
	{
		std::shared_ptr<NiceMock<MockDetectCaptureInterface>> mock_capture_if = 
			std::make_shared< NiceMock<MockDetectCaptureInterface> >();
		detect::DetectionDataHandler data_handler{};
		Image test_image{};
		bool result = data_handler.getLiveFrame(test_image);
		EXPECT_EQ(result, false);
    };

	GTEST_TEST(Test_DataHandler, getLiveFrame_should_return_true_if_capture_if_connected)
	{
		std::shared_ptr<NiceMock<MockDetectCaptureInterface>> mock_capture_if = 
			std::make_shared< NiceMock<MockDetectCaptureInterface> >();
		detect::DetectionDataHandler data_handler{};
		data_handler.attachCaptureInterface(mock_capture_if);
		Image test_image{};
		bool result = data_handler.getLiveFrame(test_image);
		EXPECT_EQ(result, true);
    };

	GTEST_TEST(Test_DataHandler, getLiveFrame_should_set_image_to_image_send_by_capture_if)
	{
		Image mock_live_image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)));
		std::shared_ptr<NiceMock<MockDetectCaptureInterface>> mock_capture_if = 
			std::make_shared< NiceMock<MockDetectCaptureInterface> >();
		EXPECT_CALL(*mock_capture_if, getImage())
			.WillOnce(Return(mock_live_image));
		detect::DetectionDataHandler data_handler{};
		data_handler.attachCaptureInterface(mock_capture_if);
		Image test_image{};
		data_handler.getLiveFrame(test_image);
		EXPECT_EQ(test_image, mock_live_image);
    };

	// Test Buffermanager
	GTEST_TEST(Test_BufferManager, addDetectedCard_should_create_new_buffer_if_no_buffers_exists)
	{
		detect::Card card(3,3);
		detect::BufferManager buffer_manager;
		buffer_manager.addDetectedCard(card, 10, 5);
		EXPECT_EQ(buffer_manager.getBuffers().size(), 1);
	}

	GTEST_TEST(Test_BufferManager, addDetectedCard_should_add_card_and_frame_to_new_buffer)
	{
		detect::Card card(3,3);
		int update_frame = 10;
		detect::BufferManager buffer_manager;
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card, update_frame, 5);
		}
		detect::Card buffered_card{};
		buffer_manager.getBuffers().at(0).getCard(buffered_card);
		EXPECT_EQ(buffered_card, card);
		EXPECT_EQ(buffer_manager.getBuffers().at(0).getLastUpdate(), update_frame);
	}

	GTEST_TEST(Test_BufferManager, addDetectedCard_should_creat_new_buffer_for_new_card)
	{
		detect::Card card_1(3,3); card_1.center_point = cv::Point(0,0);
		detect::Card card_2(4,4); card_2.center_point = cv::Point(30,30);
		int update_frame = 10;
		detect::BufferManager buffer_manager;
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_1, update_frame, 5);
		}
		buffer_manager.addDetectedCard(card_2, update_frame, 5);
		EXPECT_EQ(buffer_manager.getBuffers().size(), 2);
	}

	GTEST_TEST(Test_BufferManager, addDetectedCard_puts_card_in_corresponding_buffer)
	{
		detect::Card card_1(3,3); card_1.center_point = cv::Point(0,0);
		detect::Card card_2(4,4); card_2.center_point = cv::Point(10,10);
		detect::Card card_3(2,4); card_3.center_point = cv::Point(30,30);
		int update_frame = 10; int max_distance = 30;
		detect::BufferManager buffer_manager;
		buffer_manager.addDetectedCard(card_3, update_frame, max_distance);
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_1, update_frame, max_distance);
		}
		//This should overwrite the card in the second buffer to card_2
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_2, update_frame, max_distance);
		}
		detect::Card buffered_card{};
		buffer_manager.getBuffers().at(1).getCard(buffered_card);
		EXPECT_EQ(buffered_card, card_2);
		EXPECT_EQ(buffer_manager.getBuffers().size(), 2);
	}

	GTEST_TEST(Test_BufferManager, getBufferedCards_will_return_right_buffered_cards)
	{
		detect::Card card_1(3,3); card_1.center_point = cv::Point(0,0);
		detect::Card card_2(4,4); card_2.center_point = cv::Point(100,100);
		detect::Card card_3(2,4); card_3.center_point = cv::Point(300,300);
		int update_frame = 10; int max_distance = 30;
		detect::BufferManager buffer_manager;
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_1, update_frame, max_distance);
		}
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_2, update_frame, max_distance);
		}
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_3, update_frame, max_distance);
		}
		std::vector<detect::Card> expected_result{card_1, card_2, card_3};
		EXPECT_EQ(expected_result, buffer_manager.getBufferedCards());
	}

	GTEST_TEST(Test_removeStaleBuffers, will_remove_stale_buffers_only)
	{
		detect::Card card_1(3,3); card_1.center_point = cv::Point(0,0);
		detect::Card card_2(4,4); card_2.center_point = cv::Point(100,100);
		detect::Card card_3(2,4); card_3.center_point = cv::Point(300,300);
		int current_frame = 0; int max_distance = 30; int update_threshold = 3; 
		detect::BufferManager buffer_manager;
		for(int i=0; i<30; ++i)
		{
			buffer_manager.addDetectedCard(card_1, current_frame, max_distance);
			++current_frame;
		}
		current_frame = 0;
		for(int i=0; i<40; ++i)
		{
			buffer_manager.addDetectedCard(card_2, current_frame, max_distance);
			++current_frame;
		}
		current_frame = 0;
		for(int i=0; i<40; ++i)
		{
			buffer_manager.addDetectedCard(card_3, current_frame, max_distance);
			++current_frame;
		}
		buffer_manager.removeStaleBuffers(update_threshold, current_frame);
		std::vector<detect::Card> expected_result{card_2, card_3};
		EXPECT_EQ(expected_result, buffer_manager.getBufferedCards());
		EXPECT_EQ(buffer_manager.getBuffers().size(), 2);
	}
}