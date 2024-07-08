#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORDS 6
#define DIMENSIONS 4

int main() {
    // Initialize random number generator
    srand(time(NULL));

    // Generate weight matrices as "wordcount x four-dimensions"
    float *W_Q = (float *)malloc((WORDS * DIMENSIONS) * sizeof(float));
    float *W_K = (float *)malloc((WORDS * DIMENSIONS) * sizeof(float));
    float *W_V = (float *)malloc((WORDS * DIMENSIONS) * sizeof(float));

    for (int i = 0; i < WORDS * DIMENSIONS; i++) {
        W_Q[i] = (rand() / (RAND_MAX + 1.0)) * 0.9f; // Random values between 0 and 0.9
        W_K[i] = (rand() / (RAND_MAX + 1.0)) * 0.9f;
        W_V[i] = (rand() / (RAND_MAX + 1.0)) * 0.9f;
    }

    // Read values from "resultant.txt"
    FILE *file = fopen("resultant.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }
    float words[WORDS][6]; // Assuming 6 vectors in each row
    for (int i = 0; i < WORDS; i++) {
        for (int j = 0; j < 6; j++) {
            fscanf(file, "%f ", &words[i][j]);
        }
        fscanf(file, "\n");
    }
    fclose(file);

    // Generate queries, keys, and values using dot product multiplication
    float *Q = (float *)malloc((WORDS * DIMENSIONS) * sizeof(float));
    float *K = (float *)malloc((WORDS * DIMENSIONS) * sizeof(float));
    float *V = (float *)malloc((WORDS * DIMENSIONS) * sizeof(float));

    for (int i = 0; i < WORDS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {
            Q[i * DIMENSIONS + j] = words[i][j] * W_Q[i * DIMENSIONS + j];
            K[i * DIMENSIONS + j] = words[i][j] * W_K[i * DIMENSIONS + j];
            V[i * DIMENSIONS + j] = words[i][j] * W_V[i * DIMENSIONS + j];
        }
    }

    // Write to "qkv.txt"
    FILE *output_file = fopen("qkv.txt", "w");
    if (!output_file) {
        printf("Error opening file\n");
        return 1;
    }
// fprintf(output_file, "Queries:\n");
fprintf(output_file, "\n");
    for (int i = 0; i < WORDS; i++) {
       
        for (int j = 0; j < DIMENSIONS; j++) {
            fprintf(output_file, "%f ", Q[i * DIMENSIONS + j]);
        }
        fprintf(output_file, "\n");
        }
        
      //   fprintf(output_file, "Keys:\n");
      fprintf(output_file, "\n");
          for (int i = 0; i < WORDS; i++) {
      for (int j = 0; j < DIMENSIONS; j++) {
            fprintf(output_file, "%f ", K[i * DIMENSIONS + j]);
        }
        fprintf(output_file, "\n");
        }
       // fprintf(output_file, "Values:\n");
       fprintf(output_file, "\n");
          for (int i = 0; i < WORDS; i++) {
    for (int j = 0; j < DIMENSIONS; j++) {
            fprintf(output_file, "%f ", V[i * DIMENSIONS + j]);
        }
        fprintf(output_file, "\n");
        }
        
        

    fclose(output_file);

    // Free memory
    free(W_Q);
    free(W_K);
    free(W_V);
    free(Q);
    free(K);
    free(V);

    return 0;
}

