#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

bool is_prime(int n) {
    if(n < 2) {
        return false;
    }
    int s = (int)(sqrt(n));
    printf("Top of range: %d\n", s);
    for(int i = 2; i < s; i++) {
        if(n % i == 0) {
            printf("Not prime because of %d\n", i);
            return false;
        }
    }
    return true;
}

bool is_prime_odd_nr_optimised(int n) {
    if(n < 2) {
        return false;
    }
    int s = (int)(sqrt(n));
    printf("Top of range: %d\n", s);
    if(s > 1) {
        if(n % 2 == 0) {
            printf("Not prime because of %d\n", 2);
            return false;
        }
    }
    for(int i = 3; i < s; i += 2) {
        if(n % i == 0) {
            printf("Not prime because of %d\n", i);
            return false;
        }
    }
    return true;
}

bool is_prime_odd_and_prime_nr_optimised(int n) {
    if(n < 2) {
        return false;
    }
    int s = (int)(sqrt(n));
    printf("Top of range: %d\n", s);
    if(s > 1) {
        if(n % 2 == 0) {
            printf("Not prime because of %d\n", 2);
            return false;
        }
    }
    for(int i = 3; i <= s; i += 2) {
        int t = 1;
        for(int j = 3; j < (int)(sqrt(i)); j++) {
            if(i % j == 0) {
                t = 0; 
            }
        }
        if(t == 1) {
            if(n % i == 0) {
                printf("Not prime because of %d\n", i);
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]) {

    // Get time before execution
    clock_t begin = clock();
    
    // Testing

    //printf("%d\n", is_prime(atoi(argv[1])));

    //printf("%d\n", is_prime_odd_nr_optimised(atoi(argv[1])));

    // printf("%d\n", is_prime_odd_and_prime_nr_optimised(atoi(argv[1])));

    // Retrieve int input from command line arguments
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    // Input checking
    if(a < 1 || b < 1) {
        printf("Incorrect input. A must be smaller than B");
        return 0;
    }

    if(a > b) {
        printf("Incorrect input. A must be smaller than B");
        return 0;
    }

    // Check corner case when a == b
    if(a == b) {
        if(is_prime_odd_and_prime_nr_optimised(a)) {
            printf("%d\n", a);
            return 0;
        }
    }

    int prime_array[b - a];
    int index = 0;

    for(int i = a; i <= b; i++) {
        if(is_prime_odd_and_prime_nr_optimised(i)) {
            prime_array[index] = i;
            index++;
        }
    }

    prime_array[index] = -1;
    int c = 0;

    while(prime_array[c] != -1) {
        printf("%d ", prime_array[c]);
        c++;
    }

    // Get time after execution
    clock_t end = clock();

    // Compute difference between begin and end times to find execution duration
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nExecution time: %f\n", time_spent);

    return 0;

    // Questions

    // 1. What is the type of variables A, B, X, P?
    // Answer: int, int, int, int[]

    // 2. What C functions do we use for computing execution time?
    // Answer: clock() function

    // 3. What C header must be included for computing floor(sqrt(x))?
    // Answer: include <math.h>
}