#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int a, b, c;
    int process = 0;

    a = fork();
    if (a == 0) {
        printf("child a - PID: %d\n", getpid());
        if (getpid() % 2 != 0) {           
            fork();
            printf("other child a - PID: %d\n", getpid());
        }
        exit(0);


    } else {       
        wait(NULL);
        process++;
    }


    b = fork();
    if (b == 0) {      
        printf("child b - PID: %d\n", getpid());
        if (getpid() % 2 != 0) {            
            fork();
            printf("other child b - PID: %d\n", getpid());
        }
        exit(0);


    } else {        
        wait(NULL);
        process++;
    }


    c = fork();
    if (c == 0) {     
        printf("child c - PID: %d\n", getpid());
        if (getpid() % 2 != 0) {           
            fork();
            printf("other child c - PID: %d\n", getpid());
        }
        exit(0);


    } else {        
        wait(NULL);
        process++;
    }
    
    printf("Total processes : %d\n", process);

    return 0;
}
