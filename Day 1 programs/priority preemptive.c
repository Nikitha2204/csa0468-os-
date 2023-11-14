#include <stdio.h>
struct Process {
    int id;
    int burst_time;
    int priority;
};

int main() {
    struct Process processes[] = {
        {1, 10, 3},
        {2, 5, 1},
        {3, 8, 2},
        {4, 3, 4},
    };
    int num_processes = sizeof(processes) / sizeof(processes[0]);
	int i,j;
    printf("Priority Scheduling Process execution order:\n");
    for (i = 0; i < num_processes - 1; i++) {
        for (j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    for (i = 0; i < num_processes; i++) {
        printf("Process %d (Time %d to %d)\n", processes[i].id, current_time, current_time + processes[i].burst_time);
        current_time += processes[i].burst_time;
    }

    return 0;
}
