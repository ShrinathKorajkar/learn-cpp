#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

const int BUFFER_SIZE = 5;
sem_t empty, full, mutex;
std::vector<int> buffer;

void *producer(void *)
{
    for (int i = 0; i < 20; ++i)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        int item = i;
        buffer.push_back(item);
        std::cout << "Produced: " << item << std::endl;
        sem_post(&mutex);
        sem_post(&full);
    }
    return nullptr;
}

void *consumer(void *)
{
    for (int i = 0; i < 10; ++i)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer.back();
        buffer.pop_back();
        std::cout << "Consumed: " << item << std::endl;
        sem_post(&mutex);
        sem_post(&empty);
    }
    return nullptr;
}

int main()
{
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    // pshared - 0 (shared among threads of same process, else diff process)
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producer_thread, consumer_thread1, consumer_thread2;

    pthread_create(&producer_thread, nullptr, producer, nullptr);
    pthread_create(&consumer_thread1, nullptr, consumer, nullptr);
    pthread_create(&consumer_thread2, nullptr, consumer, nullptr);

    pthread_join(producer_thread, nullptr);
    pthread_join(consumer_thread1, nullptr);
    pthread_join(consumer_thread2, nullptr);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
