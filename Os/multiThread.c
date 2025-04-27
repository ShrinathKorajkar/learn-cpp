#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
/*
    Threads :- unit of execution within a process. threads share memory, file descriptors, code, data.
            different registers, pc, stack. less overhead of context switch.

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg);
    // returns 0 on success

    int pthread_join(pthread_t thread, void **retval);
    // retval is returned as status or exit

    void* thread_result;
    pthread_join(thread_id, &thread_result);
    if (thread_result != NULL) {
        int exit_status = *(int*)thread_result;
        printf("Thread exit status: %d\n", exit_status);
        free(thread_result);
    }

    void* thread_function(void* arg) {
        int thread_arg = *(int*)arg;
        printf("Thread argument: %d\n", thread_arg);
        // Thread logic goes here
        pthread_exit(NULL);
    }

    Program to print 1 to 10
*/
int MAX = 10;
int count = 1;
pthread_mutex_t thr;
pthread_cond_t cond;

void *even(void *arg)
{
    while (count < MAX)
    {
        pthread_mutex_lock(&thr);
        while (count % 2 != 0)
        {
            pthread_cond_wait(&cond, &thr);
        }
        printf("%d ", count++);
        pthread_mutex_unlock(&thr);
        pthread_cond_signal(&cond);
    }
    pthread_exit(0);
}

void *odd(void *arg)
{
    while (count < MAX)
    {
        pthread_mutex_lock(&thr);
        while (count % 2 != 1)
        {
            pthread_cond_wait(&cond, &thr);
        }
        printf("%d ", count++);
        pthread_mutex_unlock(&thr);
        pthread_cond_signal(&cond);
    }
    pthread_exit(0);
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_init(&thr, 0);
    pthread_cond_init(&cond, 0);
    pthread_create(&thread1, 0, &even, NULL);
    pthread_create(&thread2, 0, &odd, NULL);
    pthread_join(thread1, 0);
    pthread_join(thread2, 0);
    pthread_mutex_destroy(&thr);
    pthread_cond_destroy(&cond);
    printf("\n");
    return 0;
}