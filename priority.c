#include <stdio.h>

typedef struct {
    int id;
    int burst_time;
    int remaining_time;
    int weight;
} Process;

int main() {
    int n, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    int total_weight = 0;

    // Input
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].id = i + 1;

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burst_time);

        printf("Enter Weight (Priority): ");
        scanf("%d", &p[i].weight);

        p[i].remaining_time = p[i].burst_time;
        total_weight += p[i].weight;
    }

    printf("\n--- Execution Order ---\n");

    // Loop until all processes complete
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {

                // Time slice proportional to weight
                int time_slice = (p[i].weight * 10) / total_weight;
                if (time_slice == 0) time_slice = 1;

                if (p[i].remaining_time <= time_slice) {
                    time += p[i].remaining_time;
                    printf("P%d executed from %d to %d (Completed)\n",
                           p[i].id, time - p[i].remaining_time, time);

                    p[i].remaining_time = 0;
                    completed++;
                } else {
                    printf("P%d executed from %d to %d\n",
                           p[i].id, time, time + time_slice);

                    p[i].remaining_time -= time_slice;
                    time += time_slice;
                }
            }
        }
    }

    printf("\nAll processes completed at time %d\n", time);

    return 0;
}
