#include <stdio.h>
int main(){
    int n, tq;
    int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
    int time = 0, remain, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        printf("Enter Arrival Time of P%d: ", i+1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time of P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    remain = n;
    while(remain != 0){
        for(i = 0; i < n; i++){
            if(at[i] <= time && rt[i] > 0){
                if(rt[i] <= tq){
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;
                    remain--;
                }
                else
                {
                    rt[i] -= tq;
                    time += tq;
                }
            }
        }
        time++;
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");    float avg_wt = 0, avg_tat = 0;
    for(i = 0; i < n; i++){
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);}
    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);
    return 0;
}
