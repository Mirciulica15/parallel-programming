#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000

int num_threads = 1;

// Global variables
uint32_t counters[10] = {0};  // Counters for each digit
pthread_mutex_t mutexes[10];   // Mutexes for each counter

// Generate a random sequence of unsigned integers
void generateRandomSequence(unsigned int* sequence, int size) {
    for (int i = 0; i < size; i++) {
        sequence[i] = rand();
    }
}

// Worker function for each thread
void* countDigits(void* arg) {
    int thread_id = *((int*)arg);
    int chunk_size = ARRAY_SIZE / num_threads;
    int start = thread_id * chunk_size;
    int end = (thread_id + 1) * chunk_size;

    for (int i = start; i < end; i++) {
        unsigned int num = rand();
        while (num > 0) {
            int digit = num % 10;
            pthread_mutex_lock(&mutexes[digit]);
            counters[digit]++;
            pthread_mutex_unlock(&mutexes[digit]);
            num /= 10;
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    clock_t start = clock();

    if(argc != 2) {
        printf("Incorrect usage. Usage: ./nr-of-occurrences-threads-and-locks NUM_THREADS");
    }

    num_threads = atoi(argv[1]);

    // Initialize mutexes
    for (int i = 0; i < 10; i++) {
        pthread_mutex_init(&mutexes[i], NULL);
    }

    // Seed the random number generator
    srand(time(NULL));

    // Generate random sequence
    unsigned int sequence[ARRAY_SIZE];
    generateRandomSequence(sequence, ARRAY_SIZE);

    // Create threads
    pthread_t threads[num_threads];
    int thread_ids[num_threads];
    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, countDigits, &thread_ids[i]);
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the counters
    for (int i = 0; i < 10; i++) {
        printf("Count of digit %d: %u\n", i, counters[i]);
    }

    // Destroy mutexes
    for (int i = 0; i < 10; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);

    return 0;
}
