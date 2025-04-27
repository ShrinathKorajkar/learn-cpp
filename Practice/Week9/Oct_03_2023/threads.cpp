#include <iostream>
#include <thread>

void threadFunction1()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 1: Count " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void threadFunction2()
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 2: Count " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

int main()
{
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    std::cout << "Main thread exiting." << std::endl;

    return 0;
}
