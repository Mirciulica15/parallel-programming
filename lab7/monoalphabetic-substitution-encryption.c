#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

// Function to compute the greatest common divisor (GCD) of two numbers
unsigned int gcd(unsigned int a, unsigned int b) {
    unsigned int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute the modular multiplicative inverse
// Based on Extended Euclidean Algorithm
unsigned int mod_inverse(unsigned int a, unsigned int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to compute the permutation of the alphabet based on the key
void compute_permutation(int key, unsigned int permutation[]) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        permutation[i] = (key * i) % ALPHABET_SIZE;
    }
}

// Function to write permutation to file
void write_permutation(FILE *file, unsigned int permutation[]) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        fprintf(file, "%u ", permutation[i]);
    }
    fprintf(file, "\n");
}

// Function to encrypt or decrypt a file using the given key and permutation
void encrypt_decrypt_file(const char *input_file, const char *output_file, int key, unsigned int permutation[]) {
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");
    int ch;

    if (in_file == NULL || out_file == NULL) {
        printf("Error opening files.\n");
        exit(1);
    }

    while ((ch = fgetc(in_file)) != EOF) {
        fputc(permutation[ch], out_file);
    }

    fclose(in_file);
    fclose(out_file);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <input_file> <output_file> <encrypt/decrypt> <key>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    const char *operation = argv[3];
    int key = atoi(argv[4]);

    // Check if key is valid
    if (gcd(key, ALPHABET_SIZE) != 1) {
        printf("Invalid key. Key must be coprime with %d.\n", ALPHABET_SIZE);
        return 1;
    }

    unsigned int permutation[ALPHABET_SIZE];
    compute_permutation(key, permutation);

    // Write permutation to file
    FILE *permutation_file = fopen("permutation.txt", "w");
    write_permutation(permutation_file, permutation);
    fclose(permutation_file);

    // Perform encryption or decryption
    if (strcmp(operation, "encrypt") == 0) {
        encrypt_decrypt_file(input_file, output_file, key, permutation);
        printf("Encryption completed.\n");
    } else if (strcmp(operation, "decrypt") == 0) {
        unsigned int inverse_permutation[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            inverse_permutation[permutation[i]] = i;
        }
        encrypt_decrypt_file(input_file, output_file, mod_inverse(key, ALPHABET_SIZE), inverse_permutation);
        printf("Decryption completed.\n");
    } else {
        printf("Invalid operation. Please specify 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}
