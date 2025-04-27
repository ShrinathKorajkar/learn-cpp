#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

/*
    #Semaphore  =>  semaphore.h, fcntl
    1. int sem_init(sem_t *sem, int pshared, usigned int value)
        - pointer to semaphore
        - 0 for not shared, 1 for shared
        - initial value of semaphore

    2. int sem_destroy(sem_t *sem) -> created using init with 0 value unnamed semaphores

    3. int sem_wait(sem_t *sem)
        - performs wait operation, decrements value by 1

    4. int sem_post(sem_t *sem)
        - increments value by 1, if process are waiting, one of them is noticed

    5. int sem_getvalue(sem_t *sem, int *value)
        - retrieve value of semaphore
        - value is the pointer where value is returned

    6. sem_t *sem_open(const char *name, int oflag, ...)
        - open existing semaphore or create new one
        - flag - O_CREAT, O_EXCL

    7. int sem_close(sem_t *sem)

    8. int sem_unlink(const char *name)

*/

int main()
{
    int pipe_fd[2];
    char data[] = "Hello, receiver!";
    char ack[20];

    sem_t *sem_sender, *sem_receiver;
    sem_sender = sem_open("/sem_sender", O_CREAT, 0644, 0);
    sem_receiver = sem_open("/sem_receiver", O_CREAT, 0644, 0);

    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    pid_t child_pid = fork();
    if (child_pid == 0)
    {                      // Child process (sender)
        close(pipe_fd[0]); // Close the reading end of the pipe

        sem_wait(sem_sender); // Wait for signal from parent to write data

        // Write data to the pipe
        write(pipe_fd[1], data, strlen(data) + 1);

        sem_post(sem_receiver); // Signal parent that data is written

        close(pipe_fd[1]);
    }
    else if (child_pid > 0)
    {                      // Parent process (receiver)
        close(pipe_fd[1]); // Close the writing end of the pipe

        sem_post(sem_sender); // Signal child to write data

        sem_wait(sem_receiver); // Wait for signal from child that data is written

        char buffer[100];
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Receiver received: %s\n", buffer);

        // Send acknowledgment back to the sender
        write(pipe_fd[0], ack, strlen(ack) + 1);

        close(pipe_fd[0]);
    }
    else
    {
        perror("Fork failed");
        return 1;
    }

    sem_close(sem_sender);
    sem_close(sem_receiver);
    sem_unlink("/sem_sender");
    sem_unlink("/sem_receiver");

    return 0;
}
