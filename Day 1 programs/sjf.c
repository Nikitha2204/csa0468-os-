#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int burst_time;
};

int compare(const void *a, const void *b) {
    return ((struct Process *)a)->burst_time - ((struct Process *)b)->burst_time;
}

int main() {
    struct Process processes[] = {
        {1, 6},
        {2, 8},
        {3, 7},
        {4, 3},
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    printf("Shortest Job First (SJF) Process execution order:\n");
    qsort(processes, num_processes, sizeof(struct Process), compare);

    int current_time = 0;
	int i;
    for (i = 0; i < num_processes; i++) {
        printf("Process %d (Time %d to %d)\n", processes[i].id, current_time, current_time + processes[i].burst_time);
        current_time += processes[i].burst_time;
    }

    return 0;
}
