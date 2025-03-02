#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid_child, pid_grandchild;

    
    if ((pid_child = fork()) == 0) {

        
        if ((pid_grandchild = fork()) == 0) {
            
            printf("I am grandchild\n");

        } else {
            
            wait(NULL);
        printf("I am child\n");
        }

    } else {
        
        wait(NULL);
        printf("I am parent\n");

        
    }

    return 0;
}
