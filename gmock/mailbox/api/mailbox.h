#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

struct pollfd;

class Mailbox
{
public:
    using DataReceivedCallback = std::function<void(uint8_t byte)>;
    Mailbox(int fd, DataReceivedCallback callback);
    ~Mailbox();

private:
    void readData();
    void watchForEvents();

    int m_fd;
    DataReceivedCallback m_callback;
    bool m_terminating;
    int m_controlPipe[2];

    std::thread m_notifier;
};
