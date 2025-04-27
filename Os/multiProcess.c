#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    fork() :- sys call, used to create new child process, which runs concurrently with parent.
            Uses/copies same pc, registers, files. 0 returned to child, PID of child to parent.

    execv(), execvp() :- sys call, used to replace current process with new process.

    <unistd.h>
    pid_t fork();
    int execvp(const char *file, char *const argv[]);
    int execv(const char *path, char *const argv[]);
*/

int main()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process

        // char *args[]={"./EXEC",NULL};
        // execvp(args[0],args);

        char *command = "ls";
        char *args[] = {"ls", "-l", NULL};

        execvp(command, args);

        // execvp will only return if an error occurred
        perror("execvp");
        return 1;
    }
    else
    {
        // Parent process
        int status;

        // Wait for the child process to complete
        // wait(NULL);
        wait(&status);

        if (WIFEXITED(status))
        {
            // Child process terminated normally
            int exit_status = WEXITSTATUS(status); // can be manually given in exit(status)
            printf("Child process exited with status: %d\n", exit_status);
        }
    }

    return 0;
}