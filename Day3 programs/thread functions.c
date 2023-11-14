#include <stdio.h>
#include <pthread.h>

void* threadFunction(void* arg) {
    int thread_id = *((int*)arg);
    printf("Thread %d is running.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    pthread_create(&thread1, NULL, threadFunction, &id1);
    pthread_create(&thread2, NULL, threadFunction, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished.\n");

    int result = pthread_equal(thread1, thread2);
    if (result)
        printf("Thread 1 and Thread 2 are equal.\n");
    else
        printf("Thread 1 and Thread 2 are not equal.\n");
        
    pthread_exit(NULL);
}
