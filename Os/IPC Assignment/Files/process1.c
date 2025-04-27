/*
    This process receives data from process 2 -> sort the data -> send the data back
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "qsort.h"

void waitForConnection(FILE **control)
{
    while ((*control = fopen("./files/connection.txt", "r")) == NULL)
    {
        printf("Waiting for connection...\n");
        sleep(2);
    }
}

int getDataLength(FILE *control)
{
    int len;
    fscanf(control, "%d", &len);
    fclose(control);
    remove("./files/connection.txt");
    return len;
}

FILE *OpenSharedFile()
{
    FILE *file = fopen("./files/data.txt", "r+");
    if (file == NULL)
    {
        perror("\nError!... data not found\n");
        exit(0);
    }
    return file;
}

int *readData(int dataLength, FILE *sharedFile)
{
    int *array = malloc(dataLength * sizeof(int));
    fread(array, sizeof(int), dataLength, sharedFile);
    return array;
}

void writeData(int *data, int dataLength, FILE *sharedFile)
{
    rewind(sharedFile);
    fwrite(data, sizeof(int), dataLength, sharedFile);
}

void readNSortData(int dataLength)
{
    FILE *sharedFile = OpenSharedFile();

    flockfile(sharedFile);

    int *data = readData(dataLength, sharedFile);
    printf("Data Read\nSorting...\n");

    quickSort(data, 0, dataLength - 1);
    writeData(data, dataLength, sharedFile);

    funlockfile(sharedFile);

    fclose(sharedFile);
    free(data);
}

void sendData(FILE *control)
{
    control = fopen("./files/acknowledgement.txt", "w+");
    fprintf(control, "done");
    fclose(control);
    printf("Data sorted and sent...\n");
}

int main()
{
    printf("Process 1 Started...\n");
    FILE *control;

    waitForConnection(&control);
    printf("Connected Successfully!... Reading data\n");

    int dataLength = getDataLength(control);
    readNSortData(dataLength);

    sendData(control);

    return 0;
}
