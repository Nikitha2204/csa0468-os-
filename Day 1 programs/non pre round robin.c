#include <stdio.h>
struct Process {
    int id;
    int burst_time;
};

int main() {
    struct Process processes[] = {
        {1, 10},
        {2, 5},
        {3, 8},
        {4, 3},
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);

    printf("Non-Preemptive Round Robin Process execution order:\n");
	int i;
    for (i = 0; i < num_processes; i++) {
        printf("Process %d (Time 0 to %d)\n", processes[i].id, processes[i].burst_time);
    }

    return 0;
}

