#include <stdio.h>

#define MATRIX_SIZE 2
#define MAX_ALPHABET_SIZE 256

// Function to calculate the determinant of a 2x2 matrix modulo mod
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] + mod) % mod;
}

// Function to check if a matrix is involutory modulo mod
int is_involutory(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    // Check if the matrix squared equals the identity matrix
    int identity[MATRIX_SIZE][MATRIX_SIZE] = {{1, 0}, {0, 1}};
    int result[MATRIX_SIZE][MATRIX_SIZE] = {{0, 0}, {0, 0}};
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                result[i][j] += matrix[i][k] * matrix[k][j];
            }
            result[i][j] %= mod;
        }
    }
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (result[i][j] != identity[i][j]) {
                return 0; // Not involutory if matrix squared is not identity
            }
        }
    }
    return 1; // Involutory if matrix squared is identity
}

// Function to generate and save keys to a file
void generate_and_save_keys() {
    FILE *fptr;
    fptr = fopen("hill(2-256).txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Generate all possible keys modulo 26
    for (int i = 0; i < MAX_ALPHABET_SIZE; ++i) {
        for (int j = 0; j < MAX_ALPHABET_SIZE; ++j) {
            for (int k = 0; k < MAX_ALPHABET_SIZE; ++k) {
                for (int l = 0; l < MAX_ALPHABET_SIZE; ++l) {
                    int key[MATRIX_SIZE][MATRIX_SIZE] = {{i, j}, {k, l}};
                    
                    // Check if the key is involutory and its determinant is not a divisor of MAX_ALPHABET_SIZE
                    if (is_involutory(key, MAX_ALPHABET_SIZE) && (determinant(key, MAX_ALPHABET_SIZE) != 2) && (determinant(key, MAX_ALPHABET_SIZE) != 4) && (determinant(key, MAX_ALPHABET_SIZE) != 8) && (determinant(key, MAX_ALPHABET_SIZE) != 16) && (determinant(key, MAX_ALPHABET_SIZE) != 32) && (determinant(key, MAX_ALPHABET_SIZE) != 64) && (determinant(key, MAX_ALPHABET_SIZE) != 128)) {
                        // Save the key to the file
                        fprintf(fptr, "%d %d %d %d\n", i, j, k, l);
                    }
                }
            }
        }
    }

    fclose(fptr);
}

int main() {
    // Generate and save keys
    generate_and_save_keys();

    printf("Keys saved to hill(2-N).txt\n");

    return 0;
}
