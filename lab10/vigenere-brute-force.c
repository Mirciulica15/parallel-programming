#include <stdio.h>

#define ALPHABET_SIZE 26
#define MESSAGE_LENGTH 3

void decrypt(char *ciphertext, char *key, char *plaintext) {
    int i;
    for (i = 0; i < MESSAGE_LENGTH; i++) {
        int c = ciphertext[i] - 'A';
        int k = key[i] - 'A';
        int m = (c - k + ALPHABET_SIZE) % ALPHABET_SIZE;
        plaintext[i] = m + 'A';
    }
    plaintext[MESSAGE_LENGTH] = '\0';
}

int main() {
    FILE *keys_file = fopen("KEYS.TXT", "r");
    FILE *messages_file = fopen("MESSAGES.TXT", "w");

    if (keys_file == NULL || messages_file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char ciphertext[MESSAGE_LENGTH + 1] = "UFN";
    char key[MESSAGE_LENGTH + 1];
    char plaintext[MESSAGE_LENGTH + 1];

    while (fscanf(keys_file, "%s", key) != EOF) {
        decrypt(ciphertext, key, plaintext);
        fprintf(messages_file, "%s\n", plaintext);
    }

    fclose(keys_file);
    fclose(messages_file);

    printf("Decryption completed successfully.\n");

    return 0;
}
