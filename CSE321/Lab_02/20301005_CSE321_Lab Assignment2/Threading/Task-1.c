#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 
#define thread_num 5

void *threadFunction(void *arg) {
    int thread_id = *((int *)arg);

    printf("thread-%d running\n", thread_id);

    sleep(1);

    printf("thread-%d closed\n", thread_id);

    return NULL;
}

int main() {
    pthread_t threads[thread_num];
    int thread_ids[thread_num];

    int i = 1;
    while (i <= thread_num) {
       
        sleep(1);

        thread_ids[i - 1] = i;
        pthread_create(&threads[i - 1], NULL, threadFunction, (void *)&thread_ids[i - 1]);
        pthread_join(threads[i - 1], NULL);

        i++;
    }

    return 0;
}




