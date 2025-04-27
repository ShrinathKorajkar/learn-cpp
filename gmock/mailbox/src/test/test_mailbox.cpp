#include "mailbox.h"
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

namespace
{
class SyncFlag
{
public:
    SyncFlag()
      : m_flag(false)
    {
    }

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
    bool m_flag;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};
}  //namespace

class MailboxEvents : public Test
{
public:
    MailboxEvents()
      : m_dataPipe([] {
          array<int, 2> fds = {{-1, -1}};
          if (pipe(fds.data()) != 0) {
              throw system_error(error_code(errno, system_category()), "Could not create data pipe");
          }
          return fds;
      }())
      , m_mailbox(m_dataPipe[0], m_listenerFn)
    {
    }

    ~MailboxEvents()
    {
        m_flag.wait();
    }

protected:
    SyncFlag m_flag;
    MockFunction<void(uint8_t)> m_listener;
    std::function<void(uint8_t)> m_listenerFn = [this](uint8_t data) { m_listener.Call(data); };

    array<int, 2> m_dataPipe = {{-1, -1}};
    Mailbox m_mailbox;
};

TEST_F(MailboxEvents, Notification)
{
    uint8_t data = 0xaf;
    constexpr auto dataSize = sizeof(data);

    EXPECT_CALL(m_listener, Call(data)).WillOnce(InvokeWithoutArgs(m_flag.set));

    EXPECT_THAT(write(m_dataPipe[1], &data, dataSize), Eq(dataSize));
}
