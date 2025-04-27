#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <shared_mutex>

std::mutex mutex1, mutex2;

void thread_function()
{
    std::scoped_lock lock(mutex1, mutex2); // Lock both mutexes
    std::cout << "Thread is working." << std::endl;
}

std::recursive_mutex mtx;

void recursive_function(int depth)
{
    std::unique_lock<std::recursive_mutex> lock(mtx);
    if (depth > 0)
    {
        std::cout << "Depth " << depth << std::endl;
        recursive_function(depth - 1);
    }
    std::cout << "Depth " << depth << std::endl;
}

std::timed_mutex timedMutex;

void worker_thread()
{
    if (timedMutex.try_lock_for(std::chrono::seconds(1)))
    {
        std::cout << "Thread acquired lock." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        timedMutex.unlock();
    }
    else
    {
        std::cout << "Thread couldn't acquire lock within 1 seconds." << std::endl;
    }
}

std::shared_mutex rwLock;
int shared_resource = 0;

void reader()
{
    std::shared_lock<std::shared_mutex> lock(rwLock);
    std::cout << "Read: " << shared_resource << std::endl;
}

void writer()
{
    std::unique_lock<std::shared_mutex> lock(rwLock);
    shared_resource++;
    std::cout << "Write: " << shared_resource << std::endl;
}

int main()
{
    std::thread thread1(thread_function);
    std::thread thread2(thread_function);

    thread1.join();
    thread2.join();

    std::thread thread3(recursive_function, 5);
    thread3.join();

    std::thread thread4(worker_thread);
    std::thread thread5(worker_thread);

    thread4.join();
    thread5.join();

    std::thread writer_thread1(writer);
    std::thread writer_thread2(writer);
    std::thread reader_thread1(reader);
    std::thread reader_thread2(reader);
    std::thread reader_thread3(reader);
    std::thread writer_thread3(writer);

    reader_thread1.join();
    reader_thread2.join();
    reader_thread3.join();
    writer_thread1.join();
    writer_thread2.join();
    writer_thread3.join();
    return 0;
}
