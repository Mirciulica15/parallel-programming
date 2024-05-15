#include <stdio.h>

#define ALPHABET_SIZE 26

void generateKeys(FILE *file) {
    char key[4] = {'A', 'A', 'A', '\0'};
    int i, j, k;

    for (i = 0; i < ALPHABET_SIZE; i++) {
        for (j = 0; j < ALPHABET_SIZE; j++) {
            for (k = 0; k < ALPHABET_SIZE; k++) {
                fprintf(file, "%c%c%c\n", key[0], key[1], key[2]);
                key[2]++;
            }
            key[1]++;
            key[2] = 'A';
        }
        key[0]++;
        key[1] = 'A';
    }
}

int main() {
    FILE *file = fopen("KEYS.TXT", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    generateKeys(file);

    fclose(file);

    printf("Keys generated successfully.\n");

    return 0;
}
