#include "mailbox.h"

#include <array>
#include <poll.h>
#include <unistd.h>

using namespace std;

namespace
{
constexpr int InvalidFd = -1;
}

Mailbox::Mailbox(int fd, Mailbox::DataReceivedCallback callback)
  : m_fd(fd)
  , m_callback(callback)
  , m_terminating(false)
  , m_controlPipe{InvalidFd, InvalidFd}
{
    if (pipe(m_controlPipe) != 0) {
        throw system_error(error_code(errno, system_category()), "Could not create control pipe");
    }
    m_notifier = thread(&Mailbox::watchForEvents, this);
}

Mailbox::~Mailbox()
{
    close(m_controlPipe[1]);
    m_controlPipe[1] = InvalidFd;

    if (m_notifier.joinable()) {
        m_notifier.join();
    }

    close(m_controlPipe[0]);
    m_controlPipe[0] = InvalidFd;
}

void Mailbox::watchForEvents()
{
    array<pollfd, 2> fds;
    fds[0].fd = m_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = m_controlPipe[0];
    fds[1].events = POLLRDHUP;
    fds[1].revents = 0;

    while (true) {
        constexpr int NoTimeout = -1;
        poll(fds.data(), fds.size(), NoTimeout);

        if (fds[1].revents & POLLHUP) {
            close(fds[1].fd);
            return;
        }

        uint8_t byte;
        auto rc = read(fds[0].fd, &byte, 1);
        m_callback(byte);
    }
}
