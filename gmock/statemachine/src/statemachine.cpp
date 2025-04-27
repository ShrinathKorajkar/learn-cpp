#include "statemachine.h"

using namespace std;

StateMachine::StateMachine()
  : m_state(State::Curious)
  , m_terminating(false)
  , m_notifier(&StateMachine::monitorState, this)
{
}

StateMachine::~StateMachine()
{
    {
        lock_guard<mutex> _(m_stateMutex);
        m_terminating = true;
    }
    m_stateCv.notify_all();
    if (m_notifier.joinable()) {
        m_notifier.join();
    }
}

void StateMachine::changeState(StateMachine::State newState)
{
    {
        lock_guard<mutex> _(m_stateMutex);
        if (m_state == newState) {
            return;
        }
        m_state = newState;
        m_stateChanges.push_back(newState);
    }
    m_stateCv.notify_all();
}

void StateMachine::subscribe(StateMachine::StateChangeCallback callback)
{
    lock_guard<mutex> _(m_watchersMutex);
    m_watchers.push_back(callback);
}

void StateMachine::monitorState()
{
    while (true) {
        vector<State> stateChanges;

        {
            unique_lock<mutex> lock(m_stateMutex);
            m_stateCv.wait(lock, [this] { return !m_stateChanges.empty() || m_terminating; });
            if (m_terminating) {
                return;
            }
            swap(stateChanges, m_stateChanges);
        }

        lock_guard<mutex> _(m_watchersMutex);
        for (const auto& state : stateChanges) {
            for (const auto& callback : m_watchers) {
                callback(state);
            }
        }
    }
}
