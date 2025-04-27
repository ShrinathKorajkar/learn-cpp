#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
    This process reads the input -> send data to process 1 -> receive data from process 1 -> display the data
*/
int *takeInput(int *len)
{
    char *str = malloc(1024 * sizeof(char));

    printf("Enter numbers you want to sort : ");

    scanf("%[^\n]", str);
    *len = strlen(str);
    str = realloc(str, *len + 1);

    int *array = malloc(*len * sizeof(int));
    char *token = strtok(str, " ");

    int index = 0;
    for (; token != NULL; index++)
    {
        array[index] = atoi(token);
        token = strtok(NULL, " ");
    }
    *len = index;
    free(str);
    return array;
}

void printSortedResult(int *array, int len)
{
    printf("\nSorted elements : ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
}

int main()
{
    printf("Process 2 Started...\n");
    int len = 0;
    int *array = takeInput(&len);

    mkfifo("./fifo/myfifo", 0666);
    int pipe_fd = open("./fifo/myfifo", O_WRONLY);

    printf("Sorting...\n");
    write(pipe_fd, &len, sizeof(int));
    write(pipe_fd, array, len * sizeof(int));
    close(pipe_fd);

    pipe_fd = open("./fifo/myfifo", O_RDONLY);
    read(pipe_fd, array, len * sizeof(int));

    printSortedResult(array, len);
    close(pipe_fd);

    unlink("./fifo/myfifo");

    return 0;
}
