#include <stdio.h>

typedef struct {
    int id, weight, runtime;
} Task;

int main() {
    int n, total_time;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    Task t[n];

    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;
        printf("Task %d Weight: ", i + 1);
        scanf("%d", &t[i].weight);
        t[i].runtime = 0;
    }

    printf("Enter total simulation time: ");
    scanf("%d", &total_time);

    printf("\nProportional Scheduling:\n");

    for (int time = 0; time < total_time; time++) {
        int selected = -1;
        float min_ratio = 99999;

        for (int i = 0; i < n; i++) {
            float ratio = (float)t[i].runtime / t[i].weight;
            if (ratio < min_ratio) {
                min_ratio = ratio;
                selected = i;
            }
        }

        printf("Time %d: Task %d\n", time, t[selected].id);
        t[selected].runtime++;
    }

    return 0;
}
