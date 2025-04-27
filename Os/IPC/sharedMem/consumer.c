#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    int shmid;
    key_t key;
    char *shmaddr;

    // Generate a unique key based on a file path and an identifier.
    key = ftok(".", 'S'); // Same unique key as producer
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    struct shmid_ds shmInfo;
    long int lastDetachTime;
    do
    {
        sleep(1);
        shmctl(shmid, IPC_STAT, &shmInfo);
        lastDetachTime = shmInfo.shm_dtime;
    } while (lastDetachTime == 0);

    shmaddr = (char *)shmat(shmid, (void *)0, 0);
    printf("Message read from shared memory: %s\n", shmaddr);

    shmdt(shmaddr); // Detach from shared memory

    return 0;
}
