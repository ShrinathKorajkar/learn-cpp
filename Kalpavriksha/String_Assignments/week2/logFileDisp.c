#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Q: Read a log logfile, and parse each line into its constituent parts.
        Each line contains a timestamp, log level, and message. The timestamp is enclosed in square brackets,
        the log level is a single word, and the message may contain spaces.

    input:  3 => size of log logfile
            [2023-04-23 12:34:56] INFO Server started.
            [2023-04-23 12:35:01] WARNING Request from 192.168.0.1 denied.
            [2023-04-23 12:36:12] ERROR Database connection failed: Connection refused.

    output: Timestamp: 2023-04-23 12:34:56
            Log level: INFO
            Message: Server started.

            Timestamp: 2023-04-23 12:35:01
            Log level: WARNING
            Message: Request from 192.168.0.1 denied.

            Timestamp: 2023-04-23 12:36:12
            Log level: ERROR
            Message: Database connection failed: Connection refused.
*/

typedef struct logfile
{
    char timestamp[20];
    char logLevel[20];
    char message[100];
    struct logfile *next;
} LogFile;

void insertLog(LogFile **logdata, const char *timestamp, const char *logLevel, const char *message)
{
    LogFile *newNode = malloc(sizeof(LogFile));
    strcpy(newNode->timestamp, timestamp);
    strcpy(newNode->logLevel, logLevel);
    strcpy(newNode->message, message);
    newNode->next = NULL;

    if (*logdata == NULL)
    {
        *logdata = newNode;
        return;
    }

    LogFile *current = *logdata;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

void displayLog(LogFile *logdata)
{
    while (logdata != NULL)
    {
        printf("\nTimestamp: %s\nLog level: %s\nMessage: %s\n", logdata->timestamp, logdata->logLevel, logdata->message);
        logdata = logdata->next;
    }
}

void freeLog(LogFile *logdata)
{
    LogFile *current = logdata;
    while (current != NULL)
    {
        LogFile *next = current->next;
        free(current);
        current = next;
    }
}

int main()
{
    LogFile *logdata = NULL;
    int size;
    scanf("%d", &size);

    char timestamp[20];
    char logLevel[20];
    char message[100];
    for (int i = 0; i < size; i++)
    {
        scanf("\n");
        scanf("[%[^]] %*c %s %[^\n]", timestamp, logLevel, message);
        insertLog(&logdata, timestamp, logLevel, message);
    }

    displayLog(logdata);
    freeLog(logdata);

    return 0;
}