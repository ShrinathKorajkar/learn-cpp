#include "statemachine.h"
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

namespace
{
class SyncFlag
{
public:
    function<void()> set = [this] {
        {
            std::lock_guard<std::mutex> _(m_mutex);
            m_flag = true;
        }
        m_cv.notify_all();
    };

    void wait()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, chrono::seconds(2), [this] { return m_flag; });
    }

    bool isSet() const
    {
        return m_flag;
    }

private:
    std::mutex m_mutex;
    bool m_flag = false;
    std::condition_variable m_cv;
};
}  //namespace

class StateMachineEvents : public Test
{
public:
    StateMachineEvents() {}
    ~StateMachineEvents()
    {
        m_flag.wait();
    }

protected:
    SyncFlag m_flag;
    MockFunction<void(StateMachine::State)> m_listener;
    std::function<void(StateMachine::State)> m_listenerFn = [this](StateMachine::State newState) {
        m_listener.Call(newState);
    };
    StateMachine m_stateMachine;
};

TEST_F(StateMachineEvents, Notification)
{
    EXPECT_CALL(m_listener, Call(_)).WillOnce(InvokeWithoutArgs(m_flag.set));

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Busy);
}

TEST_F(StateMachineEvents, NotificationProvidesCorrectState)
{
    EXPECT_CALL(m_listener, Call(StateMachine::State::Busy)).WillOnce(InvokeWithoutArgs(m_flag.set));

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Busy);
}

TEST_F(StateMachineEvents, NotificationsInOrder)
{
    {
        InSequence s;
        EXPECT_CALL(m_listener, Call(StateMachine::State::Busy));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Curious));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Hungry));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Napping)).WillOnce(InvokeWithoutArgs(m_flag.set));
    }

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Busy);
    m_stateMachine.changeState(StateMachine::State::Curious);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Napping);
}

TEST_F(StateMachineEvents, NoDuplicateNotifications)
{
    {
        InSequence s;
        EXPECT_CALL(m_listener, Call(StateMachine::State::Hungry));
        EXPECT_CALL(m_listener, Call(StateMachine::State::Curious)).WillOnce(InvokeWithoutArgs(m_flag.set));
    }

    m_stateMachine.subscribe(m_listenerFn);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Hungry);
    m_stateMachine.changeState(StateMachine::State::Curious);
}
