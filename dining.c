#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_t philosophers[N];
sem_t forks[N];
sem_t room; // To avoid deadlock

// Function for philosopher behavior
void* dine(void* num) {
    int phil = *(int*)num;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", phil);
        sleep(1);

        // Limit number of philosophers trying to eat
        sem_wait(&room);

        // Pick up forks
        sem_wait(&forks[phil]);
        sem_wait(&forks[(phil + 1) % N]);

        // Eating
        printf("Philosopher %d is eating\n", phil);
        sleep(2);

        // Put down forks
        sem_post(&forks[phil]);
        sem_post(&forks[(phil + 1) % N]);

        // Leave room
        sem_post(&room);

        printf("Philosopher %d finished eating\n", phil);
    }
}

int main() {
    int i;
    int phil_num[N];

    // Initialize semaphores
    sem_init(&room, 0, N - 1); // Allow max N-1 philosophers
    for (i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (i = 0; i < N; i++) {
        phil_num[i] = i;
        pthread_create(&philosophers[i], NULL, dine, &phil_num[i]);
    }

    // Join threads
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
