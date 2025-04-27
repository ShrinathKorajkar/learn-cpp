#include <iostream>
#include <pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void *thread1_function(void *)
{
    pthread_mutex_lock(&mutex1);
    std::cout << "Thread 1: Acquired mutex1" << std::endl;

    pthread_mutex_lock(&mutex2);
    std::cout << "Thread 1: Acquired mutex2" << std::endl;

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    return nullptr;
}

void *thread2_function(void *)
{
    pthread_mutex_lock(&mutex2);
    std::cout << "Thread 2: Acquired mutex2" << std::endl;

    pthread_mutex_lock(&mutex1);
    std::cout << "Thread 2: Acquired mutex1" << std::endl;

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);
    return nullptr;
}

int main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, nullptr, thread1_function, nullptr);
    pthread_create(&thread2, nullptr, thread2_function, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    return 0;
}
