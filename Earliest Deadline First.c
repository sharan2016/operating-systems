#include <stdio.h>
typedef struct {
    int id, execution, period, remaining, deadline;
} Task;
int main() {
    int n, total_time;

    printf("Enter number of tasks: ");
    scanf("%d", &n);
    Task t[n];
    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;
        printf("Task %d Execution Time: ", i + 1);
        scanf("%d", &t[i].execution);
        printf("Task %d Period (Deadline): ", i + 1);
        scanf("%d", &t[i].period);
        t[i].remaining = 0;
        t[i].deadline = 0;
    }
    printf("Enter total simulation time: ");
    scanf("%d", &total_time);
    printf("\nEDF Scheduling:\n");
    for (int time = 0; time < total_time; time++) {
        // Release tasks
        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
                t[i].deadline = time + t[i].period;
            }
        }

        // Select earliest deadline
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (selected == -1 || t[i].deadline < t[selected].deadline) {
                    selected = i;
                }
            }
        }
        if (selected != -1) {
            printf("Time %d: Task %d (Deadline: %d)\n",
                   time, t[selected].id, t[selected].deadline);
            t[selected].remaining--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
    return 0;
}
