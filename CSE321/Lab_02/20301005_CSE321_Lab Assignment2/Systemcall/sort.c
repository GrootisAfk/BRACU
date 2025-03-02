#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int num[argc - 1];
    for (int i = 1; i < argc; i++) {
        num[i - 1] = atoi(argv[i]);
    }

    int i = 0;
    while (i < argc - 2) {
        int j = i + 1;
        while (j < argc - 1) {
            if (num[i] < num[j]) {
                int temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
            j++;
        }
        i++;
    }

    for (int i = 0; i < argc - 1; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");

    return 0;
} 







