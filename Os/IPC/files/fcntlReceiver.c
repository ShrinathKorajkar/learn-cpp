#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int file = open("ipc_file.txt", O_RDWR | O_TRUNC);
    if (file == -1)
    {
        perror("Error opening file");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    fcntl(file, F_SETLKW, &lock);

    char array[6];
    read(file, array, sizeof(array));

    for (int i = 0; i < 5; i++)
    {
        array[i] = 'a';
    }

    write(file, array, sizeof(array));

    lock.l_type = F_UNLCK;
    fcntl(file, F_SETLKW, &lock);

    close(file);

    file = open("ipc_file_control.txt", O_WRONLY | O_CREAT, 0666);
    write(file, "done", 4);
    close(file);

    return 0;
}
