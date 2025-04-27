#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> sharedVar = 0;
void increement()
{
    for (auto i = 0; i < 10; i++)
    {
        sharedVar.fetch_add(1, std::memory_order_relaxed);
    }
}
int main()
{
    sharedVar.store(1);

    std::thread th1(increement);
    std::thread th2(increement);
    th1.join();
    th2.join();

    std::cout << "Shared Variable : " << sharedVar.load() << std::endl;
    sharedVar.exchange(30);
    std::cout << "Shared Variable : " << sharedVar.load() << std::endl;
    std::cout << "is lock free : " << sharedVar.is_lock_free() << std::endl;

    int expected = 30;
    int new_value = 20;
    sharedVar.compare_exchange_strong(expected, new_value);
    std::cout << "Shared Variable : " << sharedVar.load() << std::endl;

    expected = 10;
    new_value = 15;
    sharedVar.compare_exchange_weak(expected, new_value);
    std::cout << "Shared Variable : " << sharedVar.load() << std::endl;

    return 0;
}