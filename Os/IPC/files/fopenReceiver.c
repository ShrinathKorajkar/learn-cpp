#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file = fopen("ipc_file.txt", "r+");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Lock the file
    flockfile(file);

    // char array[6];
    int array[2];
    fread(array, sizeof(int), 2, file);

    for (int i = 0; i < 2; i++)
    {
        // array[i] = 'a';
        // printf("%d ", array[i]);
        array[i] *= 2;
    }

    rewind(file);

    // Write the modified data back to the file
    fwrite(array, sizeof(int), 2, file);

    // Unlock the file
    funlockfile(file);

    // Close the file
    fclose(file);

    // Create and write to the control file
    FILE *controlFile = fopen("ipc_file_control.txt", "w+");
    if (controlFile == NULL)
    {
        perror("Error opening control file");
        return 1;
    }

    fputs("done", controlFile);

    // Close the control file
    fclose(controlFile);

    return 0;
}
