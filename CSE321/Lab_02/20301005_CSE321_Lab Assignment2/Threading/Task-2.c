
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define n_thread 5
#define n_int 5

pthread_mutex_t m;
int current = 1;

void *print_nums(void *id) {
    long tid = (long)id;

    for (int i = 0; i < n_int; ++i) {
        pthread_mutex_lock(&m);
        printf("Thread %ld prints %d\n", tid, current++);
        pthread_mutex_unlock(&m);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[n_thread];
    pthread_mutex_init(&m, NULL);

    for (long i = 0; i < n_thread; ++i) {
        if (pthread_create(&threads[i], NULL, print_nums, (void *)i) != 0) {
            fprintf(stderr, "error %ld\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (long i = 0; i < n_thread; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "error %ld\n", i);
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&m);

    return 0;
}


