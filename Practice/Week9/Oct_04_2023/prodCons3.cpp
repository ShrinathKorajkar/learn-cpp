#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>

const int BUFFER_SIZE = 5;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
std::vector<int> buffer;

void *producer(void *)
{
    for (int i = 0; i < 20; ++i)
    {
        pthread_rwlock_wrlock(&rwlock);
        while (buffer.size() >= BUFFER_SIZE)
        {
            pthread_rwlock_unlock(&rwlock);
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100 milliseconds

            pthread_rwlock_wrlock(&rwlock);
        }
        int item = i;
        buffer.push_back(item);
        std::cout << "Produced: " << item << std::endl;
        pthread_rwlock_unlock(&rwlock);
    }
    return nullptr;
}

void *consumer(void *)
{
    for (int i = 0; i < 10; ++i)
    {
        pthread_rwlock_rdlock(&rwlock);
        while (buffer.empty())
        {
            pthread_rwlock_unlock(&rwlock);
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100 milliseconds

            pthread_rwlock_wrlock(&rwlock);
        }
        int item = buffer.back();
        buffer.pop_back();
        std::cout << "Consumed: " << item << std::endl;
        pthread_rwlock_unlock(&rwlock);
    }
    return nullptr;
}

int main()
{
    pthread_t producer_thread, consumer_thread1, consumer_thread2;

    pthread_create(&producer_thread, nullptr, producer, nullptr);
    pthread_create(&consumer_thread1, nullptr, consumer, nullptr);
    pthread_create(&consumer_thread2, nullptr, consumer, nullptr);

    pthread_join(producer_thread, nullptr);
    pthread_join(consumer_thread1, nullptr);
    pthread_join(consumer_thread2, nullptr);

    return 0;
}
