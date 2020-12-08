#pragma once

#include <string>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Image.hpp"
#include "CameraSettings.hpp"
#include "CameraController.hpp"
#include "ICaptureGui.hpp"
#include "ICameraDevice.hpp"

namespace UnitTest
{

    // Mocks for Capture
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

    class MockCaptureGuiInterface : public capture::ICaptureGui
    {
        public:
            MOCK_METHOD(capture::CameraSettings, getSettings, (), (const, override));
            MOCK_METHOD(bool, checkUserInput, (), (const, override));
            MOCK_METHOD(void, setImage, (const Image& image), (override));
    };

    class CameraControllerTester: public capture::CameraController
    {
        public:
            MOCK_METHOD(void, setCameraControls, (const capture::CameraSettings& camera_settings), (override));
            void mockCamera(std::unique_ptr<capture::ICameraDevice> mock)
            {
                this->cam_.swap(mock);
                mock.release();
            }
            CameraControllerTester(): capture::CameraController(0, 0) 
            {
                //Delegates call to real CameraController method on default
                ON_CALL(*this, setCameraControls).WillByDefault(
                    [this](const capture::CameraSettings& camera_settings) {
                        //We need to give the real Object a mock cam_ object before invoking the method
                        real_.cam_.swap(this->cam_);
                        real_.setCameraControls(camera_settings);
                    }
                );
            };
        private:
            CameraController real_;
    };

}//end namespace unit tests