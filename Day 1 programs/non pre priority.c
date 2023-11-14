#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int priority;
    int burst_time;
};
int compare(const void *a, const void *b) {
    return ((struct Process *)a)->priority - ((struct Process *)b)->priority;
}

int main() {
    struct Process processes[] = {
        {1, 3, 6},
        {2, 1, 8},
        {3, 2, 7},
        {4, 4, 3},
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    printf("Non-Preemptive Priority Scheduling Process execution order:\n");
    qsort(processes, num_processes, sizeof(struct Process), compare);

    int current_time = 0;
	int i;
    for (i = 0; i < num_processes; i++) {
        printf("Process %d (Time %d to %d)\n", processes[i].id, current_time, current_time + processes[i].burst_time);
        current_time += processes[i].burst_time;
    }

    return 0;
}
