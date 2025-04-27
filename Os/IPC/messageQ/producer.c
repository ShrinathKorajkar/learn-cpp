#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
    return -1 on fail
    1. int msgget(key_t key, int msgflg);

    2. int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
        - message q identifier
        - pointer to message structure
        - size of message structure

    3. ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
        - message q identifier
        - pointer to msg struc
        - max size of message structure
        - message type - (0 for anytype)

    4. int msgctl(int msqid, int cmd, struct msqid_ds *buf);
        - cmd for action to perform
        - pointer to buf containg info used for modification

    5. struct msqid_ds{
        msg_perm, msg_stime, msg_rtime, msg_ctime, cbytes,
        msq_qnum  :-  no of messg in q
        msg_lspid :-  pid of last message sent
        msg_lrspid:-  pid of last message received
    }

    flags - 0 (block), IPC_NOWAIT
*/

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

    key = ftok(".", 'M'); // Generate unique key
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    msg.mtype = 0;
    strcpy(msg.mtext, "Hello, Message Queue!");

    msgsnd(msgid, &msg, sizeof(msg), 0);

    printf("Message sent: %s\n", msg.mtext);

     return 0;
}
