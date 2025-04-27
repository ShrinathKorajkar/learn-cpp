#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "parser.h"

/*
    Q: Parse a log file with a specified format and generate a report:
    Onput:  07-06-2023 16:11:51 dut: Device State: ON
            07-06-2023 16:11:54 dut: Device State: ERR
            07-06-2023 16:11:56 dut: Device State: ERR
            07-06-2023 16:11:58 dut: Device State: OFF
    Output: Device was on for 7 seconds
            Timestamps of error events:
            07-06-2023 16:11:54
            07-06-2023 16:11:56

    Commands To Run:
    gcc queue.c parser.c parseFile.c -o program
    ./program
*/

int main()
{
    Queue *logQ = createQueue();
    Queue *errQ = createQueue();
    FILE *ptr = fopen("./logFile.txt", "r");
    if (ptr == NULL)
    {
        printf("No such file.\n");
        return 0;
    }

    fillLogQ(ptr, logQ);

    int totalONTime = parseLogs(logQ, errQ);

    printf("Device was on for %d seconds\n", totalONTime);
    printf("Timestamps of error events:\n");
    Node *node = NULL;
    while (!isEmpty(errQ))
    {
        node = dequeue(errQ);
        printf("%s\n", node->timestamp);
        free(node);
    }

    destroyQueue(logQ);
    destroyQueue(errQ);
    fclose(ptr);

    return 0;
}
