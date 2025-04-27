#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_ARRAY_SIZE 100

struct Message
{
    long type;
    int data[MAX_ARRAY_SIZE];
    int len;
};

int main()
{
    // Create a message queue
    key_t key = ftok(".", 'M');
    int msgid = msgget(key, IPC_CREAT | 0666);

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork error");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process (receiver)

        struct Message message;
        msgrcv(msgid, &message, sizeof(message) - sizeof(long), 1, 0);

        printf("Child received array: ");
        for (int i = 0; i < message.len; i++)
        {
            printf("%d ", message.data[i]);
        }
        printf("\n");
    }
    else
    {
        // Parent process (sender)

        struct Message message;
        message.type = 1;

        // Fill the array with data
        int len = 5;
        message.len = len;
        for (int i = 0; i < len; i++)
        {
            message.data[i] = i * 2;
        }

        msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);
    }
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
