#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DIMENSIONS 6
#define MAX_LENGTH 1024

int main() {
    // Read the input file
    FILE *fp = fopen("query.txt", "r");
    char buffer[MAX_LENGTH];
    fgets(buffer, MAX_LENGTH, fp);
    fclose(fp);

    // Tokenize the input string
    char *token = strtok(buffer, " ");
    int word_count = 0;
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
        word_count++;
    }

    // Initialize the positional encoding array
    double *positional_encoding = malloc(word_count * DIMENSIONS * 
sizeof(double));

    for (int i = 0; i < word_count; i++) {
        // Calculate the positional encoding for each word
        int pos = i;
        for (int j = 0; j < DIMENSIONS; j++) {
            if ((pos & 1) == 0) {  // even position
                positional_encoding[i * DIMENSIONS + j] = sin((double)pos 
/ pow(10000.0, (2 * j) / DIMENSIONS));
            } else {  // odd position
                positional_encoding[i * DIMENSIONS + j] = cos((double)pos 
/ pow(10000.0, (2 * j + 1) / DIMENSIONS));
            }
        }
    }

    FILE *output_file = fopen("positional_encoding.txt", "w");
    for (int i = 0; i < word_count; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {
            fprintf(output_file, "%f ", positional_encoding[i * DIMENSIONS
+ j]);
        }
        fprintf(output_file, "\n");
    }

    free(positional_encoding);
    fclose(output_file);

    return 0;
}

