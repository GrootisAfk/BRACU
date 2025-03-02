#include <stdio.h>
#include <pthread.h>
#include <string.h>

int cal_ascii(const char *str) {
    int sum = 0;
    while (*str) {
        sum += *str++;
    }
    return sum;
}

int thread_func(const char *name) {
    return cal_ascii(name);
}

int main() {
    pthread_t threads[3];
    int rslt[3];

    printf("Enter three user names:\n");
    for (int i = 0; i < 3; ++i) {
        char name[100];
        scanf("%s", name);
        rslt[i] = thread_func(name);
    }

     if (rslt[0] == rslt[1] && rslt[1] == rslt[2]) {
        printf("Youreka\n");

    } else if (rslt[0] == rslt[1] || rslt[1] == rslt[2] || rslt[0] == rslt[2]) {
        printf("Miracle\n");

    } else {
        printf("Hasta la vista\n");
    }

    return 0;
}


