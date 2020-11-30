#include <string>
#include <memory>
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <opencv2/core.hpp>

#include "HelperClasses.hpp"
#include "CameraSettings.hpp"
#include "ICameraDevice.hpp"
#include "Image.hpp"

namespace UnitTest
{
	// Mocks
	class MockCam : public capture::ICameraDevice
	{
		public:
			MOCK_METHOD(bool, open, (), (override));
			MOCK_METHOD(bool, isOpened, (), (override));
			MOCK_METHOD(Image, read, (), (override));
			MOCK_METHOD(bool, set, (const int& prop_id, const int& value), (override));
			MOCK_METHOD(double, get, (const int& prop_id), (const, override));
			MOCK_METHOD(std::string, getBackendName, (), (override));
	};

	class MockGuiInterface : public capture::ICaptureGui
	{
		public:
			MOCK_METHOD(capture::CameraSettings, getSettings, (), (const, override));
			MOCK_METHOD(bool, checkUserInput, (), (const, override));
			MOCK_METHOD(void, setImage, (const Image& image), (override));
	};

	using ::testing::AtLeast;
	using ::testing::Return;
	using ::testing::_;
	using ::testing::NiceMock;

	GTEST_TEST(Test_initCamera, Should_Return_True_If_Cam_Is_Open )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, open())
			.Times(AtLeast(1));
		EXPECT_CALL(*mock_cam, isOpened())
			.WillOnce(Return(true));
		capture::CameraSettings settings{};
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool test = controller.initCamera(settings);
		EXPECT_EQ(test, true);
	}

	GTEST_TEST(Test_initCamera, Should_Return_False_If_Cam_Is_Not_Open )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, open())
			.Times(AtLeast(1));
		EXPECT_CALL(*mock_cam, isOpened())
			.WillOnce(Return(false));
		capture::CameraSettings settings{};
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		bool test = controller.initCamera(settings);
		EXPECT_EQ(test, false);
	}

	GTEST_TEST(Test_initCamera, Should_Call_Set_At_Least_Five_Times_When_Cam_Is_Opened )
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, isOpened())
			.WillOnce(Return(true));
		EXPECT_CALL(*mock_cam, set(_, _))
			.Times(AtLeast(5));
		capture::CameraSettings settings{};
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		controller.initCamera(settings);
	}

	GTEST_TEST(Test_grabLive, calls_cam_read_once)
	{
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read())
			.Times(1);
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		controller.grabLive();
	}

	GTEST_TEST(Test_grabLive, does_not_call_gui_checkUserInput_nor_setImage_if_not_conneccted )
	{
		std::shared_ptr<NiceMock<MockGuiInterface>> mock_gui = std::make_unique<NiceMock<MockGuiInterface>>();
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_gui, checkUserInput())
			.Times(0);
		EXPECT_CALL(*mock_gui, setImage(_))
			.Times(0);
		EXPECT_CALL(*mock_cam, read())
			.WillOnce(Return(Image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)))));
		CameraControllerTester controller{};
		controller.mockCamera(std::move(mock_cam));
		controller.grabLive();
	}

	GTEST_TEST(Test_grabLive, calls_gui_checkUserInput_and_setImage_once_if_connected )
	{
		std::shared_ptr<NiceMock<MockGuiInterface>> mock_gui = std::make_unique<NiceMock<MockGuiInterface>>();
		std::unique_ptr<NiceMock<MockCam>> mock_cam = std::make_unique<NiceMock<MockCam>>();
		EXPECT_CALL(*mock_cam, read())
			.WillOnce(Return(Image(cv::Mat(500, 1000, CV_8UC1, cv::Scalar(70)))));
		EXPECT_CALL(*mock_gui, checkUserInput())
			.Times(1);
		EXPECT_CALL(*mock_gui, setImage(_))
			.Times(1);
		CameraControllerTester controller{};
		controller.attachGuiInterface(mock_gui);
		controller.mockCamera(std::move(mock_cam));
		bool test = controller.grabLive();
		EXPECT_EQ(test, true);
	}

} // end namespace unit test