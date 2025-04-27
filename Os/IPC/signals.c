#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

// Signal handler function
void myHandler(int sig) {
    printf("Received signal: %d\n", sig);
}

// Signal handler function
void sigintHandler(int sig) {
    printf("Received SIGINT signal (%d). Exiting...\n", sig);
    exit(0);
}

int main() {

    // Register handler for SIGUSR1 using signal()
    signal(SIGUSR1, myHandler);
    
    // Get the current process ID
    pid_t pid = getpid();

    // Raise SIGUSR1 for itself using raise()
    printf("Raising SIGUSR1 for process %d\n", pid);
    raise(SIGUSR1);

    // Send SIGUSR1 to itself using kill()
    printf("Sending SIGUSR1 to process %d\n", pid);
    kill(pid, SIGUSR1);

    // Set handler for SIGUSR2 using sigaction()
    struct sigaction sa;
    sa.sa_handler = myHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR2, &sa, NULL);
    printf("SIGUSR2 handler set.\n");

    // Block SIGINT using sigprocmask()
    sigset_t newMask, oldMask;
    sigemptyset(&newMask);
    sigaddset(&newMask, SIGINT);
    sigprocmask(SIG_BLOCK, &newMask, &oldMask);
    printf("SIGINT is blocked.\n");

    // Rest of the code...
    
    // Restore old mask using sigprocmask()
    sigprocmask(SIG_SETMASK, &oldMask, NULL);
    printf("SIGINT is unblocked.\n");


    // Register the signal handler for SIGINT (Ctrl+C)
    signal(SIGINT, sigintHandler);

    printf("Running. Press Ctrl+C to exit.\n");

    while (1) {
        // This loop keeps the program running until SIGINT is received
        sleep(1);
        printf("Working...\n");
    }


    return 0;
}
