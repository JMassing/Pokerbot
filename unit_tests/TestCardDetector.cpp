#include <memory>

#include <gtest/gtest.h>
#include <opencv2/core.hpp>

#include "DetectionDataHandler.hpp"
#include "Detect_Mocks.hpp"
#include "ImProcSettings.hpp"


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

	GTEST_TEST(Test_DataHandler,sendDetectedCards_should_return_false_if_no_gui_if_connected)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		detect::DetectionDataHandler data_handler{};
		std::vector<detect::Card> test_cards{};
		bool result = data_handler.sendDetectedCards(test_cards);
		EXPECT_EQ(result, false);
    };

	GTEST_TEST(Test_DataHandler,sendDetectedCards_should_return_true_if_gui_connected)
	{
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		std::vector<detect::Card> test_cards{};
		bool result = data_handler.sendDetectedCards(test_cards);
		EXPECT_EQ(result, true);
    };

	GTEST_TEST(Test_DataHandler,sendDetectedCards_should_send_detected_cards)
	{
		std::vector<detect::Card> test_cards{detect::Card(2, 4), detect::Card(10,2)};
		std::shared_ptr<NiceMock<MockDetectGuiInterface>> mock_gui_if = 
			std::make_shared< NiceMock<MockDetectGuiInterface> >();
		EXPECT_CALL(*mock_gui_if, setCards(test_cards)).Times(1);
		detect::DetectionDataHandler data_handler{};
		data_handler.attachGuiInterface(mock_gui_if);
		data_handler.sendDetectedCards(test_cards);
    };

	GTEST_TEST(Test_DataHandler,getLiveFrame_should_return_false_if_no_capture_if_connected)
	{
		std::shared_ptr<NiceMock<MockDetectCaptureInterface>> mock_capture_if = 
			std::make_shared< NiceMock<MockDetectCaptureInterface> >();
		detect::DetectionDataHandler data_handler{};
		Image test_image{};
		bool result = data_handler.getLiveFrame(test_image);
		EXPECT_EQ(result, false);
    };

	GTEST_TEST(Test_DataHandler,getLiveFrame_should_return_true_if_capture_if_connected)
	{
		std::shared_ptr<NiceMock<MockDetectCaptureInterface>> mock_capture_if = 
			std::make_shared< NiceMock<MockDetectCaptureInterface> >();
		detect::DetectionDataHandler data_handler{};
		data_handler.attachCaptureInterface(mock_capture_if);
		Image test_image{};
		bool result = data_handler.getLiveFrame(test_image);
		EXPECT_EQ(result, true);
    };

	GTEST_TEST(Test_DataHandler,getLiveFrame_should_set_image_to_image_send_by_capture_if)
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

}