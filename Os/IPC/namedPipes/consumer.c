#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/*
O_RDONLY: Open for reading only.
O_WRONLY: Open for writing only.
O_RDWR: Open for reading and writing.
O_CREAT: Create the file if it doesn't exist.
O_TRUNC: Truncate the file to zero length if it exists.
O_APPEND: Append data to the file.
O_NONBLOCK: Set non-blocking mode.

S_IRUSR: Read permission for the owner.
S_IWUSR: Write permission for the owner.
S_IXUSR: Execute permission for the owner.
S_IRGRP: Read permission for the group.
S_IWGRP: Write permission for the group.
S_IXGRP: Execute permission for the group.
S_IROTH: Read permission for others.
S_IWOTH: Write permission for others.
S_IXOTH: Execute permission for others.

int fd = open("mypipe", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);


mkfifo -m 666 mypipe
echo "Hello, Consumer!" > mypipe
cat < mypipe
rm mypipe

mkfifo -m u=rw,go=r mypipe
mkfifo mypipe (o666 dfault)
*/

int main() {
    const char *fifo_name = "mypipe";
    int fd;
    char buffer[1024];

    // Open the named pipe for reading
    fd = open(fifo_name, O_RDONLY);

    // Read messages from the pipe
    read(fd, buffer, sizeof(buffer));
    printf("Consumer: Received message: %s\n", buffer);

    // Close the pipe
    close(fd);

    return 0;
}
