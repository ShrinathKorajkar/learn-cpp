/*
    This process reads the input -> send data to process 1 -> receive data from process 1 -> display the data
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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

void writeDataInFile(int *array, int len)
{
    FILE *file = fopen("./files/data.txt", "w+");

    flockfile(file);
    fwrite(array, sizeof(int), len, file);
    funlockfile(file);
    fclose(file);
}

void connectToProcess(int len)
{
    FILE *control;
    control = fopen("./files/connection.txt", "w+");
    fprintf(control, "%d", len);
    fclose(control);
}

void getAcknowledgement()
{
    FILE *acknowledge;
    while ((acknowledge = fopen("./files/acknowledgement.txt", "r")) == NULL)
    {
        printf("Sorting...\n");
        sleep(2);
    }
    fclose(acknowledge);
    remove("./files/acknowledgement.txt");
}

void receiveData(int *array, int len)
{
    FILE *file = fopen("./files/data.txt", "r");
    flockfile(file);
    fread(array, sizeof(int), len, file);
    fclose(file);
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

    writeDataInFile(array, len);

    connectToProcess(len);

    getAcknowledgement();

    receiveData(array, len);

    printSortedResult(array, len);

    return 0;
}