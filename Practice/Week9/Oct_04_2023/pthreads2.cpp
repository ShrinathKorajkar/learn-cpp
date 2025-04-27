#include <iostream>
#include <pthread.h>

struct MyStruct
{
    int age;
    std::string name;
};

void *threadFunction(void *arg)
{
    MyStruct *obj = static_cast<MyStruct *>(arg);
    int age = obj->age;
    std::string name = obj->name;
    std::cout << "Age : " << age << " Name : " << name << std::endl;
    int retValue = 20;
    return reinterpret_cast<void *>(retValue);
}

int shared_variable = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *threadFunction2(void *arg)
{
    for (int i = 0; i < 100000; ++i)
    {
        pthread_mutex_lock(&mutex);
        shared_variable++;
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main()
{
    MyStruct obj = {22, "Shri"};
    int array[] = {1, 2, 3, 4};

    pthread_t thread;
    pthread_create(&thread, NULL, threadFunction, &obj);

    void *result;
    pthread_join(thread, &result);

    int retValue = reinterpret_cast<int>(result);
    std::cout << "Return value : " << retValue << std::endl;

    //
    //
    pthread_t thread1, thread2;

    pthread_create(&thread1, nullptr, threadFunction2, nullptr);
    pthread_create(&thread2, nullptr, threadFunction2, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    std::cout << "Shared Variable: " << shared_variable << std::endl;

    return 0;
}