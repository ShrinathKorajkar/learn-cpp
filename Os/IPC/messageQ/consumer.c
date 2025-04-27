#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
    long mtype;
    char mtext[100];
};

int main()
{
    int msgid;
    key_t key;
    struct message msg;

    key = ftok(".", 'M'); // Same unique key as producer
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    msgrcv(msgid, &msg, sizeof(msg), 0, 0);
    printf("Message received: %s\n", msg.mtext);

    msgctl(msgid, IPC_RMID, NULL); // Remove message queue

    return 0;
}
