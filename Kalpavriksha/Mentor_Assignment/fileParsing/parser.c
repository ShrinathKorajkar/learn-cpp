#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

bool searchString(const char *haystack, const char *needle)
{
    char *result = strstr(haystack, needle);
    return result != NULL;
}

void substring(char *dest, char *source, int beg, int end)
{
    for (int i = beg; i < end; i++)
    {
        *dest++ = *(source + i);
    }
    *dest = '\0';
}

int differenceInTime(char *stopTime, char *startTime)
{
    int stopDay, stopMonth, stopYear, stopHour, stopMinute, stopSecond;
    int startDay, startMonth, startYear, startHour, startMinute, startSecond;

    sscanf(stopTime, "%d-%d-%d %d:%d:%d", &stopDay, &stopMonth, &stopYear, &stopHour, &stopMinute, &stopSecond);
    sscanf(startTime, "%d-%d-%d %d:%d:%d", &startDay, &startMonth, &startYear, &startHour, &startMinute, &startSecond);

    long stopSeconds = stopYear * 31536000L + stopMonth * 2592000L + stopDay * 86400L + stopHour * 3600L + stopMinute * 60L + stopSecond;
    long startSeconds = startYear * 31536000L + startMonth * 2592000L + startDay * 86400L + startHour * 3600L + startMinute * 60L + startSecond;

    long difference = stopSeconds - startSeconds;

    return (int)difference;
}

void fillLogQ(FILE *ptr, Queue *logQ)
{
    char buf[100];
    char timestamp[timestampLength];
    char deviceState[deviceStateLength];
    while (fscanf(ptr, "%[^\n]%*c", buf) == 1)
    {
        if (searchString(buf, "Device State:"))
        {
            substring(timestamp, buf, 0, 19);

            char *token = strtok(buf, " ");
            char *prevStr = NULL;
            while (token != NULL)
            {
                prevStr = token;
                token = strtok(NULL, " ");
            }
            strcpy(deviceState, prevStr);
            enqueue(logQ, timestamp, deviceState);
        }
    }
}

int parseLogs(Queue *logQ, Queue *errQ)
{
    Node *node = NULL;
    bool isON = false;
    char startTime[20];
    char stopTime[20];
    int totalONTime = 0;
    while (!isEmpty(logQ))
    {
        node = dequeue(logQ);
        if (strncmp(node->deviceState, "ON", 2) == 0 && !isON)
        {
            isON = true;
            strcpy(startTime, node->timestamp);
        }
        else if (strncmp(node->deviceState, "OFF", 3) == 0 && isON)
        {
            strcpy(stopTime, node->timestamp);
            totalONTime += differenceInTime(stopTime, startTime);
            isON = false;
        }
        else if (strncmp(node->deviceState, "ERR", 3) == 0)
        {
            enqueue(errQ, node->timestamp, node->deviceState);
        }
        free(node);
    }
    return totalONTime;
}
