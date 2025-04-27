#include <iostream>
#include <thread>
#include <future>

int add(const int &num1, const int &num2)
{
    return num1 + num2;
}

int main()
{
    std::future<int> result = std::async([]()
                                         { std::this_thread::sleep_for(std::chrono::seconds(2)); return 4; });
    std::cout << "Main thread " << std::endl;
    std::cout << "Result : " << result.get() << std::endl;

    //
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread([&promise]()
                { std::this_thread::sleep_for(std::chrono::seconds(2)); promise.set_value(4); })
        .detach();
    std::cout << "Promise" << std::endl;
    std::cout << "Future value : " << future.get() << std::endl;

    //
    std::packaged_task<int(const int &, const int &)> task(add);
    std::future<int> future2 = task.get_future();
    std::thread(std::move(task), 3, 4).detach();
    std::cout << "Task value : " << future2.get() << std::endl;

    //
    std::promise<int> p;
    std::shared_future<int> shared_result = p.get_future();

    std::thread([&p]()
                {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        p.set_value(42); })
        .detach();

    std::thread([&shared_result]()
                { std::cout << "Thread 1: " << shared_result.get() << std::endl; })
        .detach();

    std::thread([&shared_result]()
                { std::cout << "Thread 2: " << shared_result.get() << std::endl; })
        .detach();

    std::cout << "Shared result: " << shared_result.get() << std::endl;
    return 0;
}