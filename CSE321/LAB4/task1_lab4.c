#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>  

#define MAX 10         // produce and consume up to MAX 10
#define BUFLEN 6       // Buffer size
#define NUMTHREAD 2    // thread num

void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN];    // Prod source array 

int pCount = 0;         // production count
int cCount = 0;         // onsumption count
int buflen;             // Length of source array
int i = 0;              // Producer index
int j = 0;              // Consumer index

// Mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

int thread_id[NUMTHREAD] = {0, 1};

int main() {
    pthread_t thread[NUMTHREAD];
    
    // Initialize source array
    strcpy(source, "abcdef");
    buflen = strlen(source);

    // Create producer and consumer threads
    pthread_create(&thread[0], NULL, producer, (void *)&thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, (void *)&thread_id[1]);

    // Wait for both threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(void *id) {
    int thread_id = *(int *)id;

    while (pCount < MAX) {
        pthread_mutex_lock(&count_mutex); 

        // checl if buffer is full
        while (i - j >= BUFLEN) {
            pthread_cond_wait(&full, &count_mutex);
        }

        // Produce and store in buf
        buffer[i % BUFLEN] = source[pCount % buflen];
        printf("%d produced %c by Thread %d\n", pCount, buffer[i % BUFLEN], thread_id);
        i++;
        pCount++;

        // Send signal if buffer is half full
        if ((i - j) >= BUFLEN / 2) {
            pthread_cond_signal(&nonEmpty);
        }
        pthread_mutex_unlock(&count_mutex);  // Exit

        sleep(1);  
    }

    pthread_exit(NULL);
}

void *consumer(void *id) {
    int thread_id = *(int *)id;

    while (cCount < MAX) {
        pthread_mutex_lock(&count_mutex);  // Enter critical section

        // check if buffer is free or have enough items
        while ((i - j) < BUFLEN / 2) {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }

        // Consume an item 
        char conitem = buffer[j % BUFLEN];
        printf("%d consumed %c by Thread %d\n", cCount, conitem, thread_id);
        j++;
        cCount++;

        // send signal
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);  // Exit critical section

        sleep(2); 
    }

    pthread_exit(NULL);
}

