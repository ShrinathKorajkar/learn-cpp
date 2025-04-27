#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
    Named Files     =>  sys/types.h, sys/stat.h
    1. int mkfifo(const char *path, mode_t mode)
        - create named pipe in path with name (sys/stat.h)
        - mode are permissions - 000 to 777 (sys/types.h)

    2. open(path, flags) -> fcntl.h to open pipe
        - this function when used with mkfifo will wait for file to become ready or block other processes

    3. read() and write() -> unistd.h
        - block other processes while reading and writing
*/

int main()
{
    char data[] = "Hello, receiver!";
    char ack[50];

    mkfifo("./fifo/myfifo", 0666);
    int pipe_fd = open("./fifo/myfifo", O_WRONLY);

    write(pipe_fd, data, strlen(data) + 1);
    close(pipe_fd);

    pipe_fd = open("./fifo/myfifo", O_RDONLY);
    read(pipe_fd, ack, sizeof(ack));
    printf("Ack : %s \n", ack);
    close(pipe_fd);

    unlink("./fifo/myfifo");
    return 0;
}
