#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

void threadFunction(int id)
{
    for (int i = 0; i < 5; ++i)
    {
        std::string toPrint = "\nThread " + std::to_string(id) + " is running iteration " + std::to_string(i);
        std::cout << toPrint;
        std::this_thread::yield();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::once_flag flag;

void initialize_resource()
{
    std::cout << "\nResource initialization is called once";
}

void use_resource()
{
    std::call_once(flag, initialize_resource);
    std::cout << "\nhello there";
}

thread_local int thread_specific_value = 0;

void thread_function()
{
    thread_specific_value++;
    std::cout << "\nThread-specific value: " << thread_specific_value;
}

int main()
{
    std::thread thread1(threadFunction, 1);
    std::thread thread2(threadFunction, 2);

    thread1.join();
    thread2.join();

    std::cout << std::endl;

    std::thread thread4(use_resource);
    std::thread thread5(use_resource);
    std::thread thread6(use_resource);

    thread4.join();
    thread5.join();
    thread6.join();

    std::thread thread7(thread_function);
    std::thread thread8(thread_function);

    thread7.join();
    thread8.join();

    std::cout << std::endl;
    return 0;
}
