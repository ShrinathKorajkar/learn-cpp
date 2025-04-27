#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

/*
    This process reads the input -> send data to process 1 -> receive data from process 1 -> display the data
*/

int *takeInput(int *len)
{
    char *str = malloc(1024 * sizeof(char));

    printf("Enter numbers you want to sort : ");

    scanf("%[^\n]", str);
    *len = strlen(str);
    str = realloc(str, *len + 1);

    int *array = malloc(*len * sizeof(int));
    char *token = strtok(str, " ");

    int index = 0;
    for (; token != NULL; index++)
    {
        array[index] = atoi(token);
        token = strtok(NULL, " ");
    }
    *len = index;
    free(str);
    return array;
}

void printSortedResult(int *array, int len)
{
    printf("\nSorted elements : ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
}

int createSharedMemory(int len, char id)
{
    key_t key = ftok(".", id);
    return shmget(key, sizeof(int) * len, IPC_CREAT | 0666);
}

void sendData(int lenId, int dataId, int *array, int len)
{
    int *shmLenAddr = (int *)shmat(lenId, (void *)0, 0);
    int *shmDataAddr = (int *)shmat(dataId, (void *)0, 0);

    *shmLenAddr = len;
    for (int i = 0; i < len; i++)
    {
        shmDataAddr[i] = array[i];
    }

    shmdt(shmLenAddr);
    shmdt(shmDataAddr);
}

void waitForSortedData(int dataId)
{
    struct shmid_ds shmInfo;
    long int lastDetachTimeChanged = 0;
    long int lastDetachTime;
    shmctl(dataId, IPC_STAT, &shmInfo);
    lastDetachTime = shmInfo.shm_dtime;
    do
    {
        printf("Sorting...\n");
        sleep(1);
        shmctl(dataId, IPC_STAT, &shmInfo);
        lastDetachTimeChanged = shmInfo.shm_dtime;
    } while (lastDetachTime == lastDetachTimeChanged);
}

void readData(int dataId, int *array, int len)
{
    int *shmDataAddr = (int *)shmat(dataId, (void *)0, 0);

    for (int i = 0; i < len; i++)
    {
        array[i] = shmDataAddr[i];
    }
}

int main()
{
    printf("Process 2 Started...\n");
    int len = 0;
    int *array = takeInput(&len);

    int shmLenId = createSharedMemory(1, 'L');
    int shmDataId = createSharedMemory(len, 'D');

    sendData(shmLenId, shmDataId, array, len);

    waitForSortedData(shmDataId);

    readData(shmDataId, array, len);

    printSortedResult(array, len);

    shmctl(shmDataId, IPC_RMID, NULL);

    return 0;
}
