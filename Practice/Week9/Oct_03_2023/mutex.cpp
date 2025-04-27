#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

std::mutex mutex;
std::mutex mutex2;
int shared_resource = 0;
std::condition_variable cv;
bool ready = false;

void increment_resource()
{
    std::unique_lock<std::mutex> lock(mutex);
    shared_resource++;
} // automaically release resource after end

void blockingFunc()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Inside blocking function" << std::endl;
        ready = true;
    }
    cv.notify_all();
}

unsigned long maxSize = 10;
std::queue<int> queue;

void producer()
{
    for (int i = 0; i < 20; i++)
    {
        {
            std::unique_lock<std::mutex> lock(mutex2);
            if (queue.size() >= maxSize)
            {
                cv.wait(lock, []()
                        { return queue.size() < maxSize; });
            }
            queue.push(i);
            std::cout << "Produced : " << i << std::endl;
        }
        cv.notify_all();
    }
}

void consumer()
{
    for (int i = 0; i < 20; i++)
    {
        {
            std::unique_lock<std::mutex> lock(mutex2);
            if (queue.empty())
            {
                cv.wait(lock, []()
                        { return !queue.empty(); });
            }
            int item = queue.front();
            queue.pop();
            std::cout << "Consumer : " << item << std::endl;
        }
        cv.notify_all();
    }
}

int main()
{
    std::thread thread1(increment_resource);
    std::thread thread2(increment_resource);

    thread1.join();
    thread2.join();

    std::cout << "Shared Resource : " << shared_resource << std::endl;

    std::thread thread3(blockingFunc);
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, []
            { return ready; });
    std::cout << "Print after blocking function" << std::endl;
    thread3.join();

    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();

    return 0;
}
