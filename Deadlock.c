#include <stdio.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need = Max - Allocation
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], safeSeq[n];
    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    // Safety Algorithm
    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {
                    // Add allocated resources back
                    for(int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(!found) {
            printf("\nSystem is in DEADLOCK (Unsafe State)\n");
            return 0;
        }
    }

    // Safe State
    printf("\nSystem is in SAFE STATE\nSafe Sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}
