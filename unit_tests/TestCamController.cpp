#include <string>
#include <memory>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opencv2/core.hpp>

#include "CameraSettings.hpp"
#include "ICameraDevice.hpp"
#include "Image.hpp"
#include "Mocks.hpp"

namespace UnitTest
{
	
	using ::testing::AtLeast;
	using ::testing::Return;
	using ::testing::_;
	using ::testing::NiceMock;

	// Tests
	
	GTEST_TEST(Test_initCamera, Should_Return_True_If_Cam_Is_Open )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, open()).Times(AtLeast(1));
		EXPECT_CALL(*mock_cam, isOpened()).WillOnce(Return(true));
		capture::CameraSettings settings{};
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool test = controller.initCamera(settings);
		EXPECT_EQ(test, true);
	}

	GTEST_TEST(Test_initCamera, Should_Return_False_If_Cam_Is_Not_Open )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, open()).Times(AtLeast(1));
		EXPECT_CALL(*mock_cam, isOpened()).WillOnce(Return(false));
		capture::CameraSettings settings{};
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool test = controller.initCamera(settings);
		EXPECT_EQ(test, false);
	}

	GTEST_TEST(Test_initCamera, should_call_setCameraControls_when_cam_is_opened )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, isOpened()).WillOnce(Return(true));
		capture::CameraSettings settings{};
		CameraControllerTester controller{};
		EXPECT_CALL(controller, setCameraControls(_)).Times(1);
		controller.mockCamera(std::move(mock_cam));
		controller.initCamera(settings);
	}

	GTEST_TEST(Test_grabLive, calls_cam_read_once)
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read()).Times(1);
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		controller.grabLive();
	}

	GTEST_TEST(Test_grabLive, returns_true_if_image_was_grabbed )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read()).WillOnce(Return(Image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)))));
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool result = controller.grabLive();
		EXPECT_EQ(result, true);
	}

	GTEST_TEST(Test_grabLive, returns_false_if_no_image_was_grabbed )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read()).WillOnce(Return(Image{}));
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool result = controller.grabLive();
		EXPECT_EQ(result, false);
	}

	GTEST_TEST(Test_grabLive, does_not_call_gui_checkUserInput_nor_setImage_if_not_conneccted )
	{
		std::shared_ptr<NiceMock<MockGuiInterface>> mock_gui = std::make_unique<NiceMock<MockGuiInterface>>();
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_gui, checkUserInput()).Times(0);
		EXPECT_CALL(*mock_gui, setImage(_)).Times(0);
		EXPECT_CALL(*mock_cam, read()).WillOnce(Return(Image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)))));
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		controller.grabLive();
	}

	GTEST_TEST(Test_grabLive, calls_gui_checkUserInput_and_setImage_once_if_connected )
	{
		std::shared_ptr<NiceMock<MockGuiInterface>> mock_gui = std::make_unique<NiceMock<MockGuiInterface>>();
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read()).WillOnce(Return(Image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)))));
		EXPECT_CALL(*mock_gui, checkUserInput()).Times(1);
		EXPECT_CALL(*mock_gui, setImage(_)).Times(1);
		CameraControllerTester controller{};
		controller.attachGuiInterface(mock_gui);
		controller.mockCamera(std::move(mock_cam));
		bool test = controller.grabLive();
		EXPECT_EQ(test, true);
	}

	GTEST_TEST(Test_grabLive, calls_setCameraControls_on_user_input )
	{
		std::shared_ptr<NiceMock<MockGuiInterface>> mock_gui = std::make_unique<NiceMock<MockGuiInterface>>();
		EXPECT_CALL(*mock_gui, checkUserInput()).WillOnce(Return(true));
		CameraControllerTester controller{};
		EXPECT_CALL(controller, setCameraControls(_)).Times(1);
		controller.attachGuiInterface(mock_gui);
		controller.grabLive();
	}

	GTEST_TEST(Test_setCameraControls, calls_camera_set_with_auto_settings_true)
	{
		capture::CameraSettings settings{};
		NiceMock<CameraControllerTester> controller{};
 		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_AUTOFOCUS, true)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_AUTO_EXPOSURE, true)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_AUTO_WB, true)).Times(1);
		// Should not be called when auto settings are true
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_EXPOSURE, -5)).Times(0);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_FOCUS, 40)).Times(0);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_WB_TEMPERATURE, 4000)).Times(0);
		// Should always be called 
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_BRIGHTNESS, 128)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_ZOOM, 40)).Times(1);
		controller.mockCamera(std::move(mock_cam));
		controller.setCameraControls(settings);
	}

	GTEST_TEST(Test_grabVideo, returns_true_if_image_was_grabbed )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read()).WillOnce(Return(Image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)))));
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool result = controller.grabVideo();
		EXPECT_EQ(result, true);
	}

	GTEST_TEST(Test_grabVideo, returns_false_if_no_image_was_grabbed )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read()).WillOnce(Return(Image{}));
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool result = controller.grabVideo();
		EXPECT_EQ(result, false);
	}

	GTEST_TEST(Test_setCameraControls, calls_camera_set_with_auto_settings_false)
	{
		capture::CameraSettings settings{};
		settings.auto_exposure = false;
		settings.auto_focus = false;
		settings.auto_wb = false;
		NiceMock<CameraControllerTester> controller{};
 		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_AUTOFOCUS, false)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_AUTO_EXPOSURE, false)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_AUTO_WB, false)).Times(1);
		// Should be called when auto settings are false
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_EXPOSURE, -5)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_FOCUS, 40)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_WB_TEMPERATURE, 4000)).Times(1);
		// Should always be called 
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_BRIGHTNESS, 128)).Times(1);
		EXPECT_CALL(*mock_cam, set(cv::CAP_PROP_ZOOM, 40)).Times(1);
		controller.mockCamera(std::move(mock_cam));
		controller.setCameraControls(settings);
	}

} // end namespace unit test