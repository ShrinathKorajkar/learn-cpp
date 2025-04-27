#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>

void threadFunction1(int &result)
{
    std::cout << "\nThread 1 is running.";
    result = 42;
}

void threadFunction2(std::promise<int> &promise)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\nThread 2 is running.";
    promise.set_value(84);
}

int main()
{
    int thread1_result = 0;
    std::promise<int> thread2_result;

    std::thread thread1(threadFunction1, std::ref(thread1_result));
    std::thread thread2(threadFunction2, std::ref(thread2_result));

    std::thread::id thread1_id = thread1.get_id();
    std::cout << "\nThread id 1 : " << thread1_id;

    std::thread::native_handle_type handle1 = thread1.native_handle();
    std::cout << "\nHandle 1 : " << handle1;

    thread_local int thread_local_variable = 100;
    std::cout << "\nVariable : " << thread_local_variable;

    // std::mutex mutex;
    // std::scoped_lock lock(mutex);

    // std::timed_mutex timed_mutex;

    // std::unique_lock<std::mutex> unique_lock(mutex);

    // std::condition_variable cv;
    // std::condition_variable_any cv_any;

    std::thread::id this_thread_id = std::this_thread::get_id();
    std::cout << "\nThis thread id : " << this_thread_id;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    auto wake_time = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(2000);
    std::this_thread::sleep_until(wake_time);

    std::this_thread::yield();

    unsigned int num_cores = std::thread::hardware_concurrency();
    std::cout << "\nNum cores: " << num_cores;

    thread2.detach();

    thread1.swap(thread2);

    std::thread::native_handle_type native_handle = thread1.native_handle();
    std::cout << "\nnative_handle type 1 : " << native_handle;

    bool is_joinable = thread1.joinable();
    std::cout << "\nis_joinable 1 : " << is_joinable;

    std::future<int> future = std::async(std::launch::async, []()
                                         { return 123; });

    int result_from_async = future.get();
    std::cout << "\nresult from async : " << result_from_async;

    std::once_flag flag;
    std::call_once(flag, []()
                   { std::cout << "\nCalled only once."; });

    // thread1.join();
    thread2.join();

    std::cout << "\nMain thread exiting.";
    std::cout << std::endl;

    return 0;
}
