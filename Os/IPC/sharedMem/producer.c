#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

/*
    1. int shmget(key_t key, size_t size, int shmflg);
        - unique key to identify shared memory segment
        - size of shared memory
        - flags for creation and permissions  ->  IPC_CREAT, IPC_EXCL, IPC_

    2. void *shmat(int shmid, const void *shmaddr, int shmflg);
        - id of shared mem obtained from shmget
        - addr where segment is attached (NULL for system)
        - flags for attaching and permissions

    3. int shmdt(const void *shmaddr);
        - address of attached segment to detach

    4. int shmctl(int shmid, int cmd, struct shmid_ds *buf);
        - shmid of shared mem from shmget
        - control command - IPC_RMID(remove segment), IPC_SET(set info in struct), IPC_STAT(get info about struct), SHM_LOCK
        - pointer to structure for storing info

    5. struct shmid_ds {
        struct ipc_perm shm_perm;   -> ownership and permissions
        size_t shm_segsz;           -> size of segment
        time_t shm_atime;           -> last attach time
        time_t shm_dtime;           -> last detach time
        time_t shm_ctime;           -> last change time
        ...
    };

    6. struct ipc_perm {
        key_t __key;        -> Key supplied to `shmget`
        uid_t uid;          -> Owner's user ID
        gid_t gid;          -> Owner's group ID
        uid_t cuid;         -> Creator's user ID
        gid_t cgid;         -> Creator's group ID
        mode_t mode;        -> Permissions
        ...
    };

    7. Flags -> IPC_CREAT   -> create shared segment if not exist
                IPC_EXCL    -> return error if segment already exists
                SHM_RND     -> round size arg to sys page size
                SHM_REMAP   -> remap existing segment
                SHM_EXEC    -> allow exec of shared mem
                SHM_DEST    -> destroy segment
                SHM_RDONLY,  SHM_LOCK,  SHM_UNLOCK

    8. key_t ftok(const char *pathname, int proj_id);
        - returns key for pathname. file should exists
    return -1 for error
*/
int main()
{
    int shmid;
    key_t key;
    char *shmaddr;

    key = ftok(".", 'S'); // Generate unique key
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    shmaddr = (char *)shmat(shmid, (void *)0, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        return 1;
    }
    strcpy(shmaddr, "Hello, Shared Memory!");

    printf("Message written to shared memory: %s\n", shmaddr);

    shmdt(shmaddr); // Detach from shared memory
    struct shmid_ds shmInfo;
    long int lastDetachTimeChanged = 0;
    long int lastDetachTime;
    shmctl(shmid, IPC_STAT, &shmInfo);
    lastDetachTime = shmInfo.shm_dtime;
    printf("%ld", lastDetachTime);
    do
    {
        sleep(1);
        shmctl(shmid, IPC_STAT, &shmInfo);
        lastDetachTimeChanged = shmInfo.shm_dtime;
    } while (lastDetachTime == lastDetachTimeChanged);

    printf("Ack Recieved");
    shmctl(shmid, IPC_RMID, NULL);

    // Remove shared memory segment

    return 0;
}
