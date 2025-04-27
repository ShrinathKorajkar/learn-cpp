#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

class StateMachine
{
public:
    enum class State { Hungry, Curious, Busy, Napping };

    StateMachine();
    ~StateMachine();

    using StateChangeCallback = std::function<void(State newState)>;
    void subscribe(StateChangeCallback callback);

    void changeState(State newState);

private:
    void monitorState();

    std::mutex m_stateMutex;
    State m_state;
    std::vector<State> m_stateChanges;
    bool m_terminating;
    std::condition_variable m_stateCv;

    std::mutex m_watchersMutex;
    std::vector<StateChangeCallback> m_watchers;

    std::thread m_notifier;
};
