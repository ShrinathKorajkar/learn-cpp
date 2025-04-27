#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "qsort.h"

/*
    This process receives data from process 2 -> sort the data -> send the data back
*/
int createNamedPipe()
{
    mkfifo("./fifo/myfifo", 0666);
    int fifoPipe = open("./fifo/myfifo", O_RDONLY);
    return fifoPipe;
}

void readData(int fifoPipe, int **array, int(*len))
{
    read(fifoPipe, len, sizeof(int));
    *array = malloc((*len) * sizeof(int));
    read(fifoPipe, *array, (*len) * sizeof(int));
}

void sendData(int fifoPipe, int *array, int len)
{
    fifoPipe = open("./fifo/myfifo", O_WRONLY);
    write(fifoPipe, array, len * sizeof(int));
    close(fifoPipe);
    free(array);
}

int main()
{
    printf("Process 1 Started...\n");

    int fifoPipe = createNamedPipe();

    int *array = NULL;
    int len = 0;

    printf("Waiting for data...\n");
    readData(fifoPipe, &array, &len);

    printf("Data read, Sorting...\n");
    quickSort(array, 0, len - 1);

    close(fifoPipe);

    printf("Data sorted and sending...\n");
    sendData(fifoPipe, array, len);
    printf("Data sent...\n");

    return 0;
}
