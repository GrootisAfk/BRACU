#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        int i = 1;
        char *args[argc + 1];
        args[0] = "./sort";
        while (i < argc && i < 4) {
            args[i] = argv[i];
            i++;
        }
        args[i] = NULL;
        
        execvp(args[0], args);
    } else {
        wait(NULL);

        int i = 1;
        char *args[argc + 1];
        args[0] = "./oddeven";
        while (i < argc && i < 4) {
            args[i] = argv[i];
            i++;
        }
        args[i] = NULL;

        execvp(args[0], args);
    }

    return 0;
} 






