#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>
#include <SFML/Window/Event.hpp>
#include "trafficSignal.hpp"

class TestSuitForTrafficSystem : public ::testing::Test
{
public:
    std::stringstream mockcout;
    std::streambuf *realcout;
    std::stringstream mockcin;
    std::streambuf *realcin;
    void SetUp() override
    {
        realcout = std::cout.rdbuf(mockcout.rdbuf());
        realcin = std::cin.rdbuf(mockcin.rdbuf());
    }
    void TearDown() override
    {
        std::cout.rdbuf(realcout);
        std::cin.rdbuf(realcin);
    }
};

class MockForTrafficJunction : public TrafficJunction
{
public:
    MockForTrafficJunction(const int &noOfLanes) : TrafficJunction(noOfLanes) {}
    MOCK_METHOD(void, checkForUserInterrupt, (), (override));
    MOCK_METHOD(void, printStatus, (const int &), (override));
};

TEST_F(TestSuitForTrafficSystem, TrafficLight_Create)
{
    TrafficLight trafficLight(1);
    EXPECT_EQ(trafficLight.getSignalStatus(), " RED ");
}

TEST_F(TestSuitForTrafficSystem, TrafficLight_SignalController_ChangeStatus)
{
    TrafficLight trafficLight(0);
    EXPECT_EQ(trafficLight.getSignalStatus(), " RED ");
    trafficLight.stop();
    trafficLight.signalController(3, 5);
    EXPECT_EQ(trafficLight.getSignalStatus(), "GREEN");
}

TEST_F(TestSuitForTrafficSystem, TrafficLight_SignalController_ChangeStatusAfterDelay)
{
    TrafficLight trafficLight(0);
    std::thread thread(&TrafficLight::signalController, &trafficLight, 1, 4);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(trafficLight.getSignalStatus(), " RED ");

    trafficLight.stop();
    thread.join();
}

TEST_F(TestSuitForTrafficSystem, TrafficLight_SignalController_ChangeStatusAfterLoop)
{
    TrafficLight trafficLight(0);
    std::thread thread(&TrafficLight::signalController, &trafficLight, 1, 3);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(trafficLight.getSignalStatus(), " RED ");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(trafficLight.getSignalStatus(), "GREEN");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(trafficLight.getSignalStatus(), " RED ");

    trafficLight.stop();
    thread.join();
}

TEST_F(TestSuitForTrafficSystem, TrafficLight_SignalController_StopSystem)
{
    TrafficLight trafficLight(0);
    std::thread thread(&TrafficLight::signalController, &trafficLight, 1, 3);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_EQ(trafficLight.getSignalStatus(), "GREEN");

    trafficLight.stop();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    EXPECT_EQ(trafficLight.getSignalStatus(), "GREEN");
    thread.join();
}

TEST_F(TestSuitForTrafficSystem, TrafficLight_CreateMultiple_TrafficLights)
{
    TrafficLight trafficLight1(0);
    TrafficLight trafficLight2(1);
    TrafficLight trafficLight3(2);

    trafficLight1.stop();
    trafficLight2.stop();
    trafficLight3.stop();

    std::thread thread1(&TrafficLight::signalController, &trafficLight1, 1, 3);
    std::thread thread2(&TrafficLight::signalController, &trafficLight2, 1, 3);
    std::thread thread3(&TrafficLight::signalController, &trafficLight3, 1, 3);

    EXPECT_EQ(trafficLight1.getSignalStatus(), "GREEN");
    EXPECT_EQ(trafficLight2.getSignalStatus(), " RED ");
    EXPECT_EQ(trafficLight3.getSignalStatus(), " RED ");

    thread1.join();
    thread2.join();
    thread3.join();
}

TEST_F(TestSuitForTrafficSystem, TrafficJunction_CreateJunction)
{
    MockForTrafficJunction mock(3);
    EXPECT_CALL(mock, checkForUserInterrupt());
    EXPECT_CALL(mock, printStatus(::testing::_));
    mock.startTrafficLights(1);
    mock.stopTrafficLights();
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST_F(TestSuitForTrafficSystem, TrafficJunction_StopJunction)
{
    MockForTrafficJunction mock(3);
    EXPECT_CALL(mock, checkForUserInterrupt());
    EXPECT_CALL(mock, printStatus(::testing::_));
    mock.startTrafficLights(1);
    mock.stopTrafficLights();
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
    EXPECT_TRUE(mockcout.str().find("\n\nTurning Signals OFF ...") != std::string::npos);
    EXPECT_TRUE(mockcout.str().find("\nTraffic Signals Stopped") != std::string::npos);
}

TEST_F(TestSuitForTrafficSystem, TestForInput_ValidInput)
{
    int noOfLanes = 0, delayInSec = 0;
    mockcin << "3\n1\n";
    takeInput(noOfLanes, delayInSec);
    ASSERT_EQ(noOfLanes, 3);
    ASSERT_EQ(delayInSec, 1);
}

TEST_F(TestSuitForTrafficSystem, TestForInput_InvalidInput)
{
    int noOfLanes = 0, delayInSec = 0;
    mockcin << "abc\n3\nabd\n1\n";
    takeInput(noOfLanes, delayInSec);
    ASSERT_EQ(noOfLanes, 3);
    ASSERT_EQ(delayInSec, 1);
    EXPECT_TRUE(mockcout.str().find("Invalid Input !... Please enter a number") != std::string::npos);
    EXPECT_TRUE(mockcout.str().find("Invalid Input !... Please enter a positive integer") != std::string::npos);
}

TEST_F(TestSuitForTrafficSystem, TestForInput_NegativeInput)
{
    int noOfLanes = 0, delayInSec = 0;
    mockcin << "-2\n3\n-3\n1\n";
    takeInput(noOfLanes, delayInSec);
    ASSERT_EQ(noOfLanes, 3);
    ASSERT_EQ(delayInSec, 1);
    EXPECT_TRUE(mockcout.str().find("No of lanes must be greate than 2.\n\n") != std::string::npos);
    EXPECT_TRUE(mockcout.str().find("Invalid Input !... Please enter a positive integer") != std::string::npos);
}

TEST_F(TestSuitForTrafficSystem, TestForInput_LanesEdgeCase)
{
    int noOfLanes = 0, delayInSec = 0;
    mockcin << "0\n2\n3\n1\n";
    takeInput(noOfLanes, delayInSec);
    ASSERT_EQ(noOfLanes, 3);
    ASSERT_EQ(delayInSec, 1);
    EXPECT_TRUE(mockcout.str().find("No of lanes must be greate than 2.\n\n") != std::string::npos);
}