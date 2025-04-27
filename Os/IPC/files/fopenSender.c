#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    FILE *file = fopen("ipc_file.txt", "w+");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int array[] = {1, 2};

    // Write the data to the file
    fwrite(array, sizeof(int), 2, file);

    // Close the file
    fclose(file);

    // Wait for the control file to appear
    FILE *controlFile;
    while ((controlFile = fopen("ipc_file_control.txt", "r")) == NULL)
    {
        // Wait for the control file to appear
        sleep(1);
    }
    fclose(controlFile);

    // Reopen the file for reading
    file = fopen("ipc_file.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Read the data from the file
    int readArray[2];
    fread(readArray, sizeof(int), 2, file);

    // Close the file
    fclose(file);

    // Remove the control file
    remove("ipc_file_control.txt");

    for (int i = 0; i < 2; i++)
    {
        printf("%d ", readArray[i]);
    }
    printf("\n");
    // printf("Received modified array: %s\n", readArray);

    return 0;
}
