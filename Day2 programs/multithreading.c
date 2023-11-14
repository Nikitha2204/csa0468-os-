#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void* thread_function(void* thread_id) {
    int id = *((int*)thread_id);
    printf("Thread %d is running.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
	int i;
    printf("Multithreading Example\n");

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

    printf("All threads have finished.\n");

    return 0;
}
