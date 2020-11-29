#pragma once
#include <memory>

#include "CameraController.hpp"
#include "ICameraDevice.hpp"

namespace UnitTest{

    class CameraControllerTester: public capture::CameraController
    {
        public:

            void mockCamera(std::unique_ptr<capture::ICameraDevice> mock)
            {
                this->cam_.swap(mock);
                mock.release();
            }
            CameraControllerTester(): capture::CameraController(0, 0) {};
    };
}