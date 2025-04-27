#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

void *threadFunction1(void *)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 1: Count " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return nullptr;
}

void *threadFunction2(void *)
{
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 2: Count " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    return nullptr;
}

int main()
{
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, nullptr, threadFunction1, nullptr) != 0)
    {
        std::cerr << "Error creating thread 1." << std::endl;
        return 1;
    }

    if (pthread_create(&thread2, nullptr, threadFunction2, nullptr) != 0)
    {
        std::cerr << "Error creating thread 2." << std::endl;
        return 1;
    }

    if (pthread_join(thread1, nullptr) != 0)
    {
        std::cerr << "Error joining thread 1." << std::endl;
        return 1;
    }

    if (pthread_join(thread2, nullptr) != 0)
    {
        std::cerr << "Error joining thread 2." << std::endl;
        return 1;
    }

    std::cout << "Main thread exiting." << std::endl;

    return 0;
}
