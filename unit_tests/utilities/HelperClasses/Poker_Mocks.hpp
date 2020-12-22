#pragma once

#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IPokerDetect.hpp"
#include "IPokerGui.hpp"
#include "DataDetect.hpp"
#include "DataPoker.hpp"
#include "GameSettings.hpp"
#include "Game.hpp"
#include "BaseCard.hpp"

namespace UnitTest
{
    // Mocks for Poker module
    class MockPokerDetectInterface: public poker::IPokerDetect
    {
        public:
            MOCK_METHOD(detect::DataDetect, getData, (), (const, override));
    };

    class MockPokerGuiInterface: public poker::IPokerGui
    {
        public:
            MOCK_METHOD(poker::GameSettings, getSettings, (), (const, override));
            MOCK_METHOD(void, setSettings, (poker::GameSettings&), (override));
            MOCK_METHOD(bool, checkUserInput, (), (const, override));
            MOCK_METHOD(void, setData, (const poker::DataPoker&), (override));
            MOCK_METHOD(poker::DataPoker, getData, (), (override));
    };

    class MockController : public poker::IController
    {
        public:
            MOCK_METHOD(void, start, (), (override));
            MOCK_METHOD(void, stop, (), (override));
            MOCK_METHOD(void, resetPhase, (), (override));
            MOCK_METHOD(void, startNextRound, (), (override));
            MOCK_METHOD(void, setGamePhase, (), (override));
    };

    class GameTester: public poker::Game
    {
        public:
            void mockController(std::unique_ptr<poker::IController> mock)
            {
                this->controller_.swap(mock);
                mock.release();
            }
            GameTester(poker::GameSettings& settings): poker::Game(settings){ };
    };

}//end namespace unit tests