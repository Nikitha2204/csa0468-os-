#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ITERATIONS 5

int shared_counter = 0;
pthread_mutex_t mutex;

void* thread_function(void* thread_id) {
    int id = *((int*)thread_id);
    int i;
    for (i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        shared_counter++; 
        printf("Thread %d: Counter = %d\n", id, shared_counter);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
	int i;
    printf("Process Synchronization Using Mutex Locks\n");

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
        if (result) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Final Counter Value: %d\n", shared_counter);

    return 0;
}
