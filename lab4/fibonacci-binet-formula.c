#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4

typedef struct {
    int n;
    double result;
} ThreadData;

void *computeFibonacci(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int n = data->n;
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;
    data->result = (pow(phi, n) - pow(-phi, -n)) / sqrt5;
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the value of n for Fibonacci(n): ");
    scanf("%d", &n);

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];

    int fibPerThread = n / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].n = fibPerThread * (i + 1);
        pthread_create(&threads[i], NULL, computeFibonacci, (void *)&threadData[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double result = threadData[NUM_THREADS - 1].result;
    printf("Fibonacci(%d) = %.0lf\n", n, result);

    return 0;
}
