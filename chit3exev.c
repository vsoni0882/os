#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
       
        printf("\n--- CHILD PROCESS ---\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

       
        char *args[] = {"/bin/ls", "-l", NULL};
        printf("Child executing 'ls -l' using execve()...\n");

        execve("/bin/ls", args, NULL);

        perror("execve failed");
        exit(1);
    }

    else {
      
        printf("\n--- PARENT PROCESS ---\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(NULL);
        printf("Parent waited for child to finish (No zombie, No orphan).\n");

        // ----------- ZOMBIE PROCESS -----------
        // Comment out the above wait(NULL);
        // sleep(10);  // Keep parent alive to observe zombie
        // printf("Parent did NOT wait -> Child becomes zombie temporarily.\n");

        // ----------- ORPHAN PROCESS -----------
        // Uncomment this section to see orphan behavior:
        // printf("Parent exiting early to create orphan...\n");
        // exit(0);

        printf("Parent exiting normally.\n\n");
    }

    return 0;
}
