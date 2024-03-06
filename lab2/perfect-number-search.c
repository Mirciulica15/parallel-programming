#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool perfectNumberSearch(int n) {
    int sum = 0;
    for(int i = 1; i <= n / 2; i++) {
        if(n % i == 0) {
            sum += i;
        }
    }
    if (sum == n) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    // Perfect number = a number that is equal to the sum of its divisors (except itself, of course)
    // Ex: 6 = 1 + 2 + 3

    // Tests
    // printf("%d", perfectNumberSearch(6));
    // printf("%d", perfectNumberSearch(9));

    int lowerEnd = atoi(argv[1]);
    int upperEnd = atoi(argv[2]);

    for(int i = lowerEnd; i <= upperEnd; i++) {
        if(perfectNumberSearch(i) == 1) {
            printf("%d ", i);
        }
    }

    // Example usage ./perfect-number-search.o 1 2000000

    return 0;
}