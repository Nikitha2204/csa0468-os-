#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 3
#define NUM_RESOURCES 3

int max_allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
};

int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
};

int available[NUM_RESOURCES] = {3, 3, 2};

bool is_safe(int process, int request[]) {
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES];
    int i, j;

    for (i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
        finish[i] = 0;
    }

    for (i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > work[i])
            return false;
    }

    for (i = 0; i < NUM_RESOURCES; i++) {
        work[i] -= request[i];
        allocation[process][i] += request[i];
        available[i] -= request[i];
    }

    for (i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            bool can_finish = true;
            for (j = 0; j < NUM_RESOURCES; j++) {
                if (max_allocation[i][j] - allocation[i][j] > work[j]) {
                    can_finish = false;
                    break;
                }
            }
            if (can_finish) {
                finish[i] = 1;
                for (j = 0; j < NUM_RESOURCES; j++) {
                    work[j] += allocation[i][j];
                }
                i = -1;
            }
        }
    }

    for (i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i])
            return false;
    }

    return true;
}

void release_resources(int process, int release[]) {
	int i;
    for (i = 0; i < NUM_RESOURCES; i++) {
        allocation[process][i] -= release[i];
        available[i] += release[i];
    }
}

int main() {
    int request[NUM_RESOURCES] = {1, 0, 2};
    int process = 1;
	int i;
    if (is_safe(process, request)) {
        printf("Request granted. Process %d can proceed safely.\n", process);
        printf("Allocated resources after the request:\n");
        for (i = 0; i < NUM_RESOURCES; i++) {
            printf("%d ", allocation[process][i]);
        }
        printf("\n");
    } else {
        printf("Request denied. Process %d must wait to avoid deadlock.\n", process);
    }

    int release[NUM_RESOURCES] = {1, 0, 2};
    release_resources(process, release);
    printf("Resources released by Process %d.\n", process);

    return 0;
}
