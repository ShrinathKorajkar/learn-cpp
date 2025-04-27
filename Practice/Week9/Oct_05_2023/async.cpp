#include <iostream>
#include <future>
#include <thread>

int main()
{
    std::promise<int> computationPromise;
    std::future<int> computationFuture = computationPromise.get_future();

    std::thread([&computationPromise]()
                {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    int result = 42;
                    computationPromise.set_value(result); })
        .detach();

    std::future<int> asyncFuture = std::async(std::launch::async, []()
                                              {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 24; });

    std::shared_future<int> sharedFuture = computationFuture.share();

    if (asyncFuture.valid())
    {
        std::cout << "Async future is valid." << std::endl;
        int asyncResult = asyncFuture.get();
        std::cout << "Async result: " << asyncResult << std::endl;
    }
    else
    {
        std::cerr << "Async future is not valid." << std::endl;
    }

    if (computationFuture.valid())
    {
        std::cout << "Computation future is valid." << std::endl;
        int computationResult = computationFuture.get();
        std::cout << "Computation result: " << computationResult << std::endl;
    }
    else
    {
        std::cerr << "Computation future is not valid." << std::endl;
    }

    if (sharedFuture.valid())
    {
        std::cout << "Shared future is valid." << std::endl;
        int sharedResult = sharedFuture.get();
        std::cout << "Shared result: " << sharedResult << std::endl;
    }
    else
    {
        std::cerr << "Shared future is not valid." << std::endl;
    }

    if (asyncFuture.valid())
    {
        auto asyncStatus = asyncFuture.wait_for(std::chrono::seconds(0));
        if (asyncStatus == std::future_status::timeout)
        {
            std::cout << "Async future is not ready yet." << std::endl;
        }
        else if (asyncStatus == std::future_status::ready)
        {
            int asyncResult = asyncFuture.get();
            std::cout << "Async result: " << asyncResult << std::endl;
        }
    }

    auto sharedStatus = sharedFuture.wait_until(
        std::chrono::system_clock::now() + std::chrono::seconds(3));
    if (sharedStatus == std::future_status::timeout)
    {
        std::cout << "Shared future is not ready yet." << std::endl;
    }
    else if (sharedStatus == std::future_status::ready)
    {
        int sharedResult = sharedFuture.get();
        std::cout << "Shared result: " << sharedResult << std::endl;
    }

    return 0;
}
