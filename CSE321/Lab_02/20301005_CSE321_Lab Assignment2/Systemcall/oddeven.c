#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int i = 1;
    while (i < argc) {
        int num = atoi(argv[i]);
        if (num % 2 == 0) {
            printf("%d is even\n", num);
        } else {
            printf("%d is odd\n", num);
        }
        i++;
    }

    return 0;
} 

