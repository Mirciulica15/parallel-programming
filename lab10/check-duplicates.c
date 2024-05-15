#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 4
#define MAX_KEYS 17576
#define MAX_MESSAGES 17576

int checkDuplicates(char **words, int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                printf("Duplicate found: %s\n", words[i]);
                return 1;
            }
        }
    }
    return 0;
}

int readWordsFromFile(char *filename, char **words, int max_words) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", filename);
        return -1;
    }

    int count = 0;
    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF && count < max_words) {
        words[count] = strdup(word);
        count++;
    }

    fclose(file);
    return count;
}

int main() {
    char *keys[MAX_KEYS];
    char *messages[MAX_MESSAGES];

    int num_keys = readWordsFromFile("KEYS.TXT", keys, MAX_KEYS);
    int num_messages = readWordsFromFile("MESSAGES.TXT", messages, MAX_MESSAGES);

    if (num_keys == -1 || num_messages == -1) {
        return 1;
    }

    printf("Checking for duplicates in KEYS.TXT...\n");
    if (!checkDuplicates(keys, num_keys)) {
        printf("No duplicates found in KEYS.TXT.\n");
    }

    printf("\nChecking for duplicates in MESSAGES.TXT...\n");
    if (!checkDuplicates(messages, num_messages)) {
        printf("No duplicates found in MESSAGES.TXT.\n");
    }

    // Free allocated memory
    int i;
    for (i = 0; i < num_keys; i++) {
        free(keys[i]);
    }
    for (i = 0; i < num_messages; i++) {
        free(messages[i]);
    }

    return 0;
}
