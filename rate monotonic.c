#include <stdio.h>
typedef struct {
    int id, execution, period, remaining;
} Task;
int main() {
    int n, hyperperiod;

    printf("Enter number of tasks: ");
    scanf("%d", &n);
    Task t[n];
    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;
        printf("Task %d Execution Time: ", i + 1);
        scanf("%d", &t[i].execution);
        printf("Task %d Period: ", i + 1);
        scanf("%d", &t[i].period);
        t[i].remaining = 0;
    }
    printf("Enter total simulation time: ");
    scanf("%d", &hyperperiod);

    printf("\nRMS Scheduling:\n");

    for (int time = 0; time < hyperperiod; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (time % t[i].period == 0) {
                t[i].remaining = t[i].execution;
            }
        }

        // Select highest priority (smallest period)
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0) {
                if (selected == -1 || t[i].period < t[selected].period) {
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", time, t[selected].id);
            t[selected].remaining--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
    return 0;
}
