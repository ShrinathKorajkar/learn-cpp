#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int file = open("ipc_file.txt", O_WRONLY | O_CREAT, 0666);
    if (file == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char array[] = "hello";

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    fcntl(file, F_SETLKW, &lock);

    write(file, array, sizeof(array));

    lock.l_type = F_UNLCK;
    fcntl(file, F_SETLKW, &lock);

    close(file);

    while (access("ipc_file_control.txt", F_OK) != 0)
    {
        // Wait for the control file to appear
        sleep(1);
    }

    file = open("ipc_file.txt", O_RDONLY);
    read(file, array, sizeof(array));
    close(file);

    remove("ipc_file_control.txt");

    printf("Received modified array: ");
    printf("%s ", array);
    printf("\n");

    return 0;
}
