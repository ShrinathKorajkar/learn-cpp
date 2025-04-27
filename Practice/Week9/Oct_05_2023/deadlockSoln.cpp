#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void thread1_function()
{
    while (true)
    {
        if (mutex1.try_lock() == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (mutex2.try_lock() == 0)
            {
                std::cout << "Thread 1: Acquired mutex1 and mutex2" << std::endl;
                mutex2.unlock();
                break;
            }
            mutex1.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void thread2_function()
{
    while (true)
    {
        if (mutex2.try_lock() == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (mutex1.try_lock() == 0)
            {
                std::cout << "Thread 2: Acquired mutex1 and mutex2" << std::endl;
                mutex1.unlock();
                break;
            }
            mutex2.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    std::thread thread1(thread1_function);
    std::thread thread2(thread2_function);

    thread1.join();
    thread2.join();

    return 0;
}
