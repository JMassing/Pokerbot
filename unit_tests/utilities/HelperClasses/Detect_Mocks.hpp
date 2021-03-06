#pragma once

#include <vector>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Image.hpp"
#include "Card.hpp"
#include "ImProcSettings.hpp"
#include "IDetectGui.hpp"
#include "IDetectCapture.hpp"

namespace UnitTest
{
    // Mocks for Detection module
    class MockDetectCaptureInterface: public detect::IDetectCapture
    {
        public:
            MOCK_METHOD(Image, getImage, (), (const, override));
    };

    class MockDetectGuiInterface: public detect::IDetectGui
    {
        public:
            MOCK_METHOD(detect::ImProcSettings, getSettings, (), (const, override));
            MOCK_METHOD(bool, checkUserInput, (), (const, override));
            MOCK_METHOD(void, setCards, (std::vector<detect::Card>), (override));
    };

    class MockDetectionDataHandler: public detect::IDetectionDataHandler
    {
        public:
            MOCK_METHOD(bool, getLiveFrame, (Image&), (const, override));
            MOCK_METHOD(bool, getProcessingSettings, (detect::ImProcSettings&), (override));
            MOCK_METHOD(bool, sendDetectedCards, (const std::vector<detect::Card>&), (const, override));
    };
}//end namespace unit tests