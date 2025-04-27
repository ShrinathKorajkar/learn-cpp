#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char *fifo_name = "mypipe";
    int fd;

    // Create the named pipe
    mkfifo(fifo_name, 0666);

    // Open the named pipe for writing
    fd = open(fifo_name, O_WRONLY);

    // Send messages through the pipe
    write(fd, "Hello, Consumer!", sizeof("Hello, Consumer!"));

    // Close the pipe
    close(fd);

    // Remove the named pipe
    unlink(fifo_name);

    return 0;
}
