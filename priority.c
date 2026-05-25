#include <stdio.h>
#include <limits.h>

int i, j, n;

/* -------- PRIORITY NON-PREEMPTIVE -------- */
void priority_non_preemptive() {
    int bt[20], wt[20], tat[20], pr[20], p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter BT and Priority for P%d: ", i+1);
        scanf("%d%d", &bt[i], &pr[i]);
        p[i] = i+1;
    }

    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if(pr[i] > pr[j]) {
                int temp;
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i];  p[i] = p[j];  p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for(i = 1; i < n; i++)
        wt[i] = wt[i-1] + bt[i-1];

    for(i = 0; i < n; i++)
        tat[i] = wt[i] + bt[i];

    printf("\nProcess\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
}

/* -------- PRIORITY PREEMPTIVE -------- */
void priority_preemptive() {
    int bt[20], rt[20], pr[20], wt[20], tat[20];
    int time = 0, completed = 0, highest, idx;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter BT and Priority for P%d: ", i+1);
        scanf("%d%d", &bt[i], &pr[i]);
        rt[i] = bt[i];
    }

    while(completed != n) {
        highest = INT_MAX;
        idx = -1;

        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && pr[i] < highest) {
                highest = pr[i];
                idx = i;
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if(rt[idx] == 0) {
            completed++;
            tat[idx] = time;
            wt[idx] = tat[idx] - bt[idx];
        }
    }

    printf("\nProcess\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, bt[i], pr[i], wt[i], tat[i]);
}

/* -------- MAIN -------- */
int main() {
    int choice;

    do {
        printf("\n--- Priority Scheduling ---\n");
        printf("1. Non-Preemptive Priority\n");
        printf("2. Preemptive Priority\n");
        printf("3. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: priority_non_preemptive(); break;
            case 2: priority_preemptive(); break;
            case 3: printf("Exit\n"); break;
            default: printf("Invalid choice\n");
        }

    } while(choice != 3);

    return 0;
}
