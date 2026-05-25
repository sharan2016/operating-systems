#include <stdio.h>
#include <limits.h>

int i, j, n;

/* -------- SJF NON-PREEMPTIVE -------- */
void sjf_non_preemptive() {
    int bt[20], wt[20], tat[20], p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        p[i] = i+1;
    }

    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if(bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for(i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for(i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("\nProcess\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
}

/* -------- SJF PREEMPTIVE (SRTF) -------- */
void sjf_preemptive() {
    int bt[20], rt[20], wt[20], tat[20];
    int time = 0, completed = 0, min, shortest;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter BT for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    while(completed != n) {
        min = INT_MAX;
        shortest = -1;

        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;
        time++;

        if(rt[shortest] == 0) {
            completed++;
            tat[shortest] = time;
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
}

/* -------- MAIN -------- */
int main() {
    int choice;

    do {
        printf("\n--- SJF Scheduling ---\n");
        printf("1. Non-Preemptive SJF\n");
        printf("2. Preemptive SJF (SRTF)\n");
        printf("3. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: sjf_non_preemptive(); break;
            case 2: sjf_preemptive(); break;
            case 3: printf("Exit\n"); break;
            default: printf("Invalid choice\n");
        }

    } while(choice != 3);

    return 0;
}
