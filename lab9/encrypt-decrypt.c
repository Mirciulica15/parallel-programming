#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MATRIX_SIZE 2
#define ALPHABET_SIZE 26

// Function to perform matrix multiplication modulo mod
void matrix_multiply(int matrix[MATRIX_SIZE][MATRIX_SIZE], int vector[MATRIX_SIZE], int result[MATRIX_SIZE], int mod) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
        result[i] %= mod;
        if (result[i] < 0) {
            result[i] += mod; // Get the complement if result is negative
        }
    }
}

// Function to encrypt a message using a 2x2 key matrix and modulo 26
void encrypt(char *message, int key[MATRIX_SIZE][MATRIX_SIZE], char *encrypted_message) {
    int len = strlen(message);
    int vector[MATRIX_SIZE];
    int result[MATRIX_SIZE];

    // Initialize encrypted message to empty string
    encrypted_message[0] = '\0';

    for (int i = 0; i < len; i += MATRIX_SIZE) {
        // Convert characters to numbers (A=0, B=1, ..., Z=25)
        for (int j = 0; j < MATRIX_SIZE; j++) {
            vector[j] = message[i + j] - 'A';
        }

        // Multiply the key matrix with the vector modulo 26
        matrix_multiply(key, vector, result, ALPHABET_SIZE);

        // Append encrypted characters to the encrypted message
        for (int j = 0; j < MATRIX_SIZE; j++) {
            encrypted_message[strlen(encrypted_message)] = result[j] + 'A';
        }
    }
}

// Function to calculate the modular multiplicative inverse of an integer
int modular_inverse(int a, int mod) {
    for (int i = 1; i < mod; i++) {
        if ((a * i) % mod == 1) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to calculate the inverse of a 2x2 matrix modulo mod
void inverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + mod) % mod;
    int det_inverse = modular_inverse(det, mod);
    result[0][0] = matrix[1][1] * det_inverse % mod;
    result[0][1] = (-matrix[0][1] * det_inverse) % mod;
    result[1][0] = (-matrix[1][0] * det_inverse) % mod;
    result[1][1] = matrix[0][0] * det_inverse % mod;

    // Ensure all elements are positive
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (result[i][j] < 0) {
                result[i][j] += mod;
            }
        }
    }
}

// Function to decrypt an encrypted message using the inverse of the key matrix
void decrypt(char *ciphertext, int key_inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(ciphertext);
    int vector[MATRIX_SIZE];
    int result[MATRIX_SIZE];

    printf("Decrypted message: ");
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        // Convert characters to numbers (A=0, B=1, ..., Z=25)
        for (int j = 0; j < MATRIX_SIZE; j++) {
            vector[j] = ciphertext[i + j] - 'A';
        }

        // Multiply the key inverse matrix with the vector modulo 26
        matrix_multiply(key_inverse, vector, result, ALPHABET_SIZE);

        // Print decrypted characters
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%c", result[j] + 'A');
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    // Generate a random invertible key matrix
    int key[MATRIX_SIZE][MATRIX_SIZE];
    int key_inverse[MATRIX_SIZE][MATRIX_SIZE];
    do {
        // Generate random integers for the key matrix elements
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                key[i][j] = rand() % ALPHABET_SIZE; // Random value modulo ALPHABET_SIZE (26)
            }
        }
        // Calculate the inverse of the key matrix
        inverse(key, key_inverse, ALPHABET_SIZE);
    } while (key_inverse[0][0] == -1); // Repeat until a valid key inverse is found

    // Example message
    char message[] = "HELLO";
    char encrypted_message[strlen(message) + 1]; // +1 for null terminator

    // Encrypt the message and store the encrypted message
    encrypt(message, key, encrypted_message);

    printf("Original message: %s\n", message);
    printf("Encrypted message: %s\n", encrypted_message);

    // Decrypt the encrypted message
    decrypt(encrypted_message, key_inverse);

    return 0;
}
