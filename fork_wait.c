#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void demo_fork_wait() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    } 
    else if (pid == 0) {
        printf("\n[Child Process]\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child is running...\n");
        sleep(2);
        printf("Child completed.\n");
        _exit(0);  // safely exit child without killing main program
    } 
    else {
        wait(NULL);
        printf("\n[Parent Process]\n");
        printf("Parent PID: %d\n", getpid());
        printf("Parent resumes after child termination.\n");
    }
}

void demo_zombie() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("\n[Child Process]\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child exiting immediately...\n");
        _exit(0); // child exits safely
    } 
    else {
        printf("\n[Parent Process]\n");
        printf("Parent sleeping for 10 seconds...\n");
        printf("During this time, the child becomes a Zombie.\n");
        printf("Run this in another terminal: ps -l | grep %d\n", pid);
        sleep(10);
        printf("Parent waking up and exiting, zombie cleared.\n");
        wait(NULL); // reap the zombie
    }
}

void demo_orphan() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("\n[Parent Process]\n");
        printf("Parent PID: %d\n", getpid());
        printf("Parent exiting before child.\n");
        // Don't use exit(0) here — just return to keep main alive
        return;
    } 
    else if (pid == 0) {
        sleep(5);
        printf("\n[Child Process]\n");
        printf("Child PID: %d, New Parent PID (adopted by init): %d\n", getpid(), getppid());
        printf("Child still running after parent exit (Orphan Process).\n");
        _exit(0);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n==============================");
        printf("\n Process Control System Calls ");
        printf("\n==============================");
        printf("\n1. Demonstrate fork() and wait()");
        printf("\n2. Demonstrate Zombie process");
        printf("\n3. Demonstrate Orphan process");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: demo_fork_wait(); break;
            case 2: demo_zombie(); break;
            case 3: demo_orphan(); break;
            case 4: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }

        printf("\n--------------------------------------------\n");
    }
    return 0;
}    