#include <stdio.h>
#define MAX 50
int isPresent(int frames[], int f, int page) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}
void fifo(int pages[], int n, int f) {
    int frames[f], index = 0, faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, f, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
    }

    printf("\nFIFO Page Faults = %d\n", faults);
}
void lru(int pages[], int n, int f) {
    int frames[f], time[f], counter = 0, faults = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < f; j++) {
                if (time[j] < time[lruIndex])
                    lruIndex = j;
            }

            frames[lruIndex] = pages[i];
            counter++;
            time[lruIndex] = counter;
            faults++;
        }
    }

    printf("LRU Page Faults = %d\n", faults);
}
void optimal(int pages[], int n, int f) {
    int frames[f], faults = 0;

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (isPresent(frames, f, pages[i]))
            continue;

        int index = -1, farthest = i + 1;

        for (int j = 0; j < f; j++) {
            int k;
            for (k = i + 1; k < n; k++) {
                if (frames[j] == pages[k]) {
                    if (k > farthest) {
                        farthest = k;
                        index = j;
                    }
                    break;
                }
            }

            if (k == n) {
                index = j;
                break;
            }
        }

        if (index == -1)
            index = 0;

        frames[index] = pages[i];
        faults++;
    }

    printf("Optimal Page Faults = %d\n", faults);
}
int main() {
    int pages[MAX], n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}
