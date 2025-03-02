#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("1. Parent process ID: 0\n");
    pid_t child_pid = fork();

    if (child_pid == 0) {     
        printf("2. Child process ID: %d\n", getpid());

        int i = 0;
        while (i < 3) {
            pid_t grandchild_pid = fork();

            if (grandchild_pid == 0) {              
                printf("%d. Grand Child process ID: %d\n", i + 3, getpid());
                break; 
                
            } else {
                wait(NULL); 
            }

            i++;
        }
    } else {
        wait(NULL); 
    }

    return 0;
} 

