#include <string>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HelperClasses.hpp"
#include "CameraSettings.hpp"
#include "ICameraDevice.hpp"

namespace UnitTest
{
	// Mocks
	class MockCam : public capture::ICameraDevice
	{
		public:
			MOCK_METHOD(bool, open, (), (override));
			MOCK_METHOD(bool, isOpened, (), (override));
			MOCK_METHOD(bool, read, (), (override));
			MOCK_METHOD(bool, set, (const int& prop_id, const int& value), (override));
			MOCK_METHOD(double, get, (const int& prop_id), (const, override));
			MOCK_METHOD(std::string, getBackendName, (), (override));
	};

	using ::testing::AtLeast;
	using ::testing::Return;
	using ::testing::_;
	using ::testing::NiceMock;

	GTEST_TEST(TestCamController, initCamera_Should_Return_True_If_Cam_Is_Open )
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

	GTEST_TEST(TestCamController, initCamera_Should_Return_False_If_Cam_Is_Not_Open )
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

	GTEST_TEST(TestCamController, initCamera_ShouldCall_Set_At_Least_Five_Times_When_Cam_Is_Opened )
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
} // end namespace unit test