#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    char buffer[30];
    char ack[] = "Data received and acknowledged.";

    mkfifo("./fifo/myfifo", 0666);
    int pipe_fd = open("./fifo/myfifo", O_RDONLY);

    read(pipe_fd, buffer, sizeof(buffer));
    printf("Receiver received: %s\n", buffer);
    close(pipe_fd);

    pipe_fd = open("./fifo/myfifo", O_WRONLY);
    write(pipe_fd, ack, strlen(ack) + 1);
    close(pipe_fd);

    return 0;
}
