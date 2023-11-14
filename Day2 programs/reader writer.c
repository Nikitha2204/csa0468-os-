#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_resource = 0; 

sem_t rw_mutex;  
sem_t resource_access;  

// Reader function
void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        sem_wait(&rw_mutex);  
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);
        sem_post(&rw_mutex); 
        sleep(1);
    }
    pthread_exit(NULL);
}

// Writer function
void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&resource_access);  
        sem_wait(&rw_mutex);  
        shared_resource++;
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);
        sem_post(&rw_mutex); 
        sem_post(&resource_access); 
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    sem_init(&rw_mutex, 0, 1); 
    sem_init(&resource_access, 0, 1);  

    printf("Reader-Writer Problem Simulation\n");
	int i;
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&resource_access);

    return 0;
}
