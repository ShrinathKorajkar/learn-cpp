#include <iostream>
#include <pthread.h>
#include <vector>

const int BUFFER_SIZE = 5;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

std::vector<int> buffer;

void *producer(void *)
{
    for (int i = 0; i < 20; ++i)
    {
        pthread_mutex_lock(&mutex);
        while (buffer.size() == BUFFER_SIZE)
        {
            pthread_cond_wait(&cond_producer, &mutex);
        }
        int item = i;
        buffer.push_back(item);
        std::cout << "Produced: " << item << std::endl;
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void *consumer(void *)
{
    for (int i = 0; i < 10; ++i)
    {
        pthread_mutex_lock(&mutex);
        while (buffer.empty())
        {
            pthread_cond_wait(&cond_consumer, &mutex);
        }
        int item = buffer.back();
        buffer.pop_back();
        std::cout << "Consumed: " << item << std::endl;
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);
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
