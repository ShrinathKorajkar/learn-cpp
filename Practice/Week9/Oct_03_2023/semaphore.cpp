#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    explicit Semaphore(int count) : count_(count) {}

    void Acquire()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ <= 0)
        {
            condition_.wait(lock);
        }
        count_--;
    }

    void Release()
    {
        std::unique_lock<std::mutex> lock(mutex_);
        count_++;
        condition_.notify_one();
    }

private:
    int count_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

Semaphore semaphore(1);

void worker(int id)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    semaphore.Acquire();
    std::cout << "Worker " << id << " is working." << std::endl;
    semaphore.Release();
}

int main()
{
    std::thread workers[5];
    for (int i = 0; i < 5; ++i)
    {
        workers[i] = std::thread(worker, i);
    }

    for (int i = 0; i < 5; ++i)
    {
        workers[i].join();
    }

    return 0;
}
