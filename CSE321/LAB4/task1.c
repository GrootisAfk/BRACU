#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10 // producers and consumers can produce and consume up to MAX
#define BUFLEN 6
#define NUMTHREAD 2 /* number of threads */

void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN]; // from this array producer will store its production into buffer
int pCount = 0;
int cCount = 0;
int buflen;

// initializing pthread mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = {0, 1};
int i = 0;
int j = 0;

void *producer(void *id) {
    for (i = 0; i < MAX; i++) {
        pthread_mutex_lock(&count_mutex);

        while (pCount == BUFLEN) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        buffer[pCount] = source[pCount % buflen];
        printf("%d produced %c by Thread %d\n", i, buffer[pCount], *(int *)id);
        pCount++;
        
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
    }
    pthread_exit(NULL);
}

void *consumer(void *id) {
    for (j = 0; j < MAX; j++) {
        pthread_mutex_lock(&count_mutex);

        while (pCount == 0) {
            pthread_cond_wait(&full, &count_mutex);
        }

        printf("%d consumed %c by Thread %d\n", j, buffer[cCount], *(int *)id);
        cCount++;
        pCount--;

        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
    }
    pthread_exit(NULL);
}

int main() {
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];
    strcpy(source, "abcdef");
    buflen = strlen(source);

    /* create 2 threads */
    /* create one consumer and one producer */
    /* define the properties of multi-threads for both threads */
    pthread_create(&thread[0], NULL, producer, &thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, &thread_id[1]);

    for (i = 0; i < NUMTHREAD; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
