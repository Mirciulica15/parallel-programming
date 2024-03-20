#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

#define MAX_THREADS 16

typedef struct {
    int start;
    int end;
    int thread_id;
} ThreadArg;

void fibonacci(int n, mpz_t result) {
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;
    
    mpz_set_d(result, round((pow(phi, n) - pow(1 - phi, n)) / sqrt5));
}

void *fibonacci_range(void *arg) {
    ThreadArg *thread_arg = (ThreadArg *)arg;

    for (int i = thread_arg->start; i <= thread_arg->end; i++) {
        mpz_t fib_i;
        mpz_init(fib_i);
        fibonacci(i, fib_i);
        printf("Thread %d: The %d-th Fibonacci number is: ", thread_arg->thread_id, i);
        mpz_out_str(stdout, 10, fib_i);
        printf("\n");
        mpz_clear(fib_i);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <N> <num_threads>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    if (num_threads <= 0 || num_threads > MAX_THREADS) {
        printf("Number of threads must be between 1 and %d\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[MAX_THREADS];
    ThreadArg thread_args[MAX_THREADS];

    int step = N / num_threads;
    int current_start = 1;

    clock_t start = clock();
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].start = current_start;
        thread_args[i].end = current_start + step - 1;
        thread_args[i].thread_id = i + 1;
        if (i == num_threads - 1) {
            // Ensure the last thread covers the remaining range
            thread_args[i].end = N;
        }
        pthread_create(&threads[i], NULL, fibonacci_range, (void *)&thread_args[i]);
        current_start += step;
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
