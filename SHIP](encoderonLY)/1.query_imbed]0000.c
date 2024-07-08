#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LENGTH 256
#define MAX_WORD_LENGTH 64
#define EMBEDDING_DIMENSION 6

int main() {
    FILE *index_file = fopen("index.txt", "r");
    FILE *query_file = fopen("query.txt", "r");

    if (index_file == NULL || query_file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    char index_buffer[MAX_LINE_LENGTH];
    char query_buffer[MAX_LINE_LENGTH];

    int i, j;
    int *index_map = (int *)malloc(1000 * sizeof(int));
    for (i = 0; i < 1000; i++) {
        index_map[i] = -1;
    }

    int line_number = 0;

    while (fgets(index_buffer, MAX_LINE_LENGTH, index_file) != NULL) {
        char *word = strtok(index_buffer, "\n");
        for (j = 0; j < strlen(word); j++) {
            if (word[j] == ' ') {
                word[j] = '\0';
                break;
            }
        }

        for (i = 1; i <= line_number; i++) {
            if (!strcmp(index_buffer, index_file)) {
                index_map[i - 1] = i;
                break;
            }
        }

        line_number++;
    }

    fclose(index_file);

    while (fgets(query_buffer, MAX_LINE_LENGTH, query_file) != NULL) {
        char *word = strtok(query_buffer, "\n");
        for (j = 0; j < strlen(word); j++) {
            if (word[j] == ' ') {
                word[j] = '\0';
                break;
            }
        }

        for (i = 1; i <= line_number; i++) {
            if (!strcmp(word, index_buffer)) {
                printf("%s [%.6f, %.6f, %.6f, %.6f, %.6f, %.6f]\n",
                    word,
                    (double)rand() / RAND_MAX,
                    (double)rand() / RAND_MAX,
                    (double)rand() / RAND_MAX,
                    (double)rand() / RAND_MAX,
                    (double)rand() / RAND_MAX
                );
                break;
            }
        }

        if (i > line_number) {
            printf("%s [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]\n", word);
        }
    }

    fclose(query_file);

    return 0;
}

