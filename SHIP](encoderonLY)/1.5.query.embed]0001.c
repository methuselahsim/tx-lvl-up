#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMBEDDING_DIM 6

int main() {
    FILE *query_file = fopen("query.txt", "r");
    if (query_file == NULL) {
        printf("Error opening query file.\n");
        return 1;
    }

    FILE *query_embeds_file = fopen("query_embeds.txt", "w");
    if (query_embeds_file == NULL) {
        printf("Error opening query embeds file.\n");
        fclose(query_file);
        return 1;
    }

    char word[100];
    srand(time(NULL)); // seed the random number generator

    while (fscanf(query_file, "%99s\n", word) == 1) {
        float embed[EMBEDDING_DIM];

        for (int i = 0; i < EMBEDDING_DIM; i++) {
            embed[i] = (float)rand() / RAND_MAX;
        }

    //    fprintf(query_embeds_file, "%s [", word);
        for (int i = 0; i < EMBEDDING_DIM; i++) {
            fprintf(query_embeds_file, "%f ", embed[i]);
        }
        fprintf(query_embeds_file, "\n");
    }

    fclose(query_file);
    fclose(query_embeds_file);

    return 0;
}

