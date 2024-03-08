#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Received signal %d from keyboard\n", sig);
}

void child_process(int signal_to_send) {
    printf("Child process %d started, waiting for signal...\n", getpid());
    pause(); // Wait for any signal
}

int main() {
    signal(SIGINT, handle_sigint); // Catch keyboard interrupt signal

    int child1 = fork();
    if (child1 == 0) {
        // First child process
        child_process(SIGUSR1);
        printf("Child 1 received SIGUSR1, exiting...\n");
        exit(0);
    }

    int child2 = fork();
    if (child2 == 0) {
        // Second child process
        child_process(SIGUSR2);
        printf("Child 2 received SIGUSR2, exiting...\n");
        exit(0);
    }

    // Parent process
    printf("Parent process, press DEL (or Ctrl+C) to send signals to children...\n");
    pause(); // Wait for SIGINT

    printf("Parent process received keyboard interrupt, sending signals to children...\n");
    kill(child1, SIGUSR1); // Send SIGUSR1 to child1
    kill(child2, SIGUSR2); // Send SIGUSR2 to child2

    // Wait for children to exit
    wait(NULL);
    wait(NULL);

    printf("Parent process exiting...\n");
    return 0;
}
