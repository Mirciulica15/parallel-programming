#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fibonacci(unsigned long n, mpz_t result) {
    double sqrt5 = sqrt(5);
    double phi = (1 + sqrt5) / 2;
    
    mpz_set_d(result, round((pow(phi, n) - pow(1 - phi, n)) / sqrt5));
}

void fibonacci2(unsigned long n, mpz_t result) {
    mpz_t sqrt5, phi, temp1, temp2;
    mpz_inits(sqrt5, phi, temp1, temp2, NULL);
    
    mpz_set_ui(sqrt5, 5);
    mpz_sqrt(sqrt5, sqrt5);

    mpz_set_ui(phi, 1);
    mpz_add_ui(phi, phi, 5);
    mpz_sqrt(phi, phi);
    mpz_tdiv_q_ui(phi, phi, 2);

    mpz_pow_ui(temp1, phi, n);
    mpz_neg(sqrt5, sqrt5);
    mpz_powm_ui(temp2, sqrt5, n, phi);

    mpz_add_ui(phi, phi, 1);
    mpz_divexact_ui(phi, phi, 2);

    mpz_sub(result, phi, temp2);
    mpz_tdiv_q(result, result, sqrt5);

    mpz_clears(sqrt5, phi, temp1, temp2, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    mpz_t fib_n;
    mpz_init(fib_n);
    
    clock_t start = clock();

    fibonacci(n, fib_n);
    //fibonacci2(n, fib_n);
    
    clock_t end = clock();

    printf("The %d-th Fibonacci number is: ", n);
    mpz_out_str(stdout, 10, fib_n);
    printf("\n");

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_spent);
    
    // Clean up
    mpz_clear(fib_n);
    
    return 0;
}
