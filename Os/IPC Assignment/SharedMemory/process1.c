#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include "qsort.h"

/*
    This process receives data from process 2 -> sort the data -> send the data back
*/

int createSharedMemory(int len, char id)
{
    key_t key = ftok(".", id);
    return shmget(key, sizeof(int) * len, IPC_CREAT | 0666);
}

void waitForData(int shmLenId)
{
    struct shmid_ds shmInfo;
    long int lastDetachTime;
    do
    {
        sleep(1);
        printf("Waiting for data...\n");
        shmctl(shmLenId, IPC_STAT, &shmInfo);
        lastDetachTime = shmInfo.shm_dtime;
    } while (lastDetachTime == 0);
}

int getLengthOfData(int shmLenId)
{
    int *shmLenAddr = (int *)shmat(shmLenId, (void *)0, 0);
    int len = *shmLenAddr;
    shmdt(shmLenAddr);
    shmctl(shmLenId, IPC_RMID, NULL);
    return len;
}

int *readData(int *shmDataAddr, int len)
{
    int *array = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        array[i] = shmDataAddr[i];
    }
    return array;
}

void sendData(int *shmDataAddr, int *array, int len)
{
    for (int i = 0; i < len; i++)
    {
        shmDataAddr[i] = array[i];
    }

    shmdt(shmDataAddr);
    printf("Data sent\n");
}

int main()
{
    printf("Process 1 Started...\n");

    int shmLenId = createSharedMemory(1, 'L');

    waitForData(shmLenId);

    int len = getLengthOfData(shmLenId);

    int shmDataId = createSharedMemory(len, 'D');
    int *shmDataAddr = (int *)shmat(shmDataId, (void *)0, 0);

    int *array = readData(shmDataAddr, len);

    printf("Data read, Sorting...\n");
    quickSort(array, 0, len - 1);

    printf("Data sorted and sending...\n");
    sendData(shmDataAddr, array, len);
    return 0;
}
