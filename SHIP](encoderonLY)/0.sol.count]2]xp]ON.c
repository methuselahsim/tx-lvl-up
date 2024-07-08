#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100
#define MAX_CORPUS_SIZE 10000

int main() {
    FILE *corpus_file = fopen("corpus.txt", "r");
    if (corpus_file == NULL) {
        printf("Error opening corpus file.\n");
        return 1;
    }

    int word_count = 0;
    char word[MAX_WORD_LENGTH];
    int unique_word_count = 0;

    // Store unique words in an array of character pointers
    char *unique_words[10000];   // assuming max unique words is less than 10,000
    for (int i = 0; i < 10000; i++) {
        unique_words[i] = NULL;
    }

    FILE *index_file = fopen("index.txt", "w");
    if (index_file == NULL) {
        printf("Error opening index file.\n");
        return 1;
    }

    while (fscanf(corpus_file, "%s\n", word) > 0) {
        if (strlen(word) == 0) continue;   // skip empty lines

        int found = 0;
        for (int i = 0; i < unique_word_count; i++) {
            if (strcmp(word, unique_words[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Create a copy of each word and store it in the array
            char *unique_word = strdup(word);
            unique_words[unique_word_count++] = unique_word;

            fprintf(index_file, "%d %s\n", ++word_count, word);
        }
    }

    for (int i = 0; i < unique_word_count; i++) {
        free(unique_words[i]);
    }

    fclose(corpus_file);
    fclose(index_file);

    return 0;
}
