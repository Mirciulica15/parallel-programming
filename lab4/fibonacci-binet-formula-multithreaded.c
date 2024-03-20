#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

// Define the structure to hold thread arguments
typedef struct {
    unsigned long n;
    mpz_t result;
} ThreadArg;

// Fibonacci function for each thread
void *fibonacci_thread(void *arg) {
    ThreadArg *thread_arg = (ThreadArg *)arg;
    unsigned long n = thread_arg->n;
    mpz_init(thread_arg->result);

    // Calculate Fibonacci number
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;
    mpz_set_d(thread_arg->result, round((pow(phi, n) - pow(1 - phi, n)) / sqrt5));

    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <num_threads>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    // Create thread IDs and attributes
    pthread_t threads[num_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Allocate memory for thread arguments
    ThreadArg thread_args[num_threads];

    clock_t start = clock();

    // Create threads
    for (int i = 0; i < num_threads; ++i) {
        thread_args[i].n = n;
        pthread_create(&threads[i], &attr, fibonacci_thread, (void *)&thread_args[i]);
    }

    // Join threads and accumulate results
    mpz_t fib_n;
    mpz_init(fib_n);
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
        mpz_add(fib_n, fib_n, thread_args[i].result);
    }

    clock_t end = clock();

    printf("The %d-th Fibonacci number is: ", n);
    mpz_out_str(stdout, 10, fib_n);
    printf("\n");

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    // Clean up
    mpz_clear(fib_n);
    pthread_attr_destroy(&attr);

    return 0;
}
