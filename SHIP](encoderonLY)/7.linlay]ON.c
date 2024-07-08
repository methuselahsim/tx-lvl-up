#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Read shatt_ mbed data from file
    FILE *fp = fopen("shatt_mbed.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    double shatt_mbed[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fscanf(fp, "%lf", &shatt_mbed[i][j]);
        }
    }

    fclose(fp);

    // Create weights data and write to file
    double weights[6][6];
    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            weights[i][j] = (double)rand() / RAND_MAX * 0.98 + 0.01;
        }
    }

    fp = fopen("weights.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fprintf(fp, "%lf ", weights[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    // Multiply shatt_mbed and weights
    double shatt_emb_train_0[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            shatt_emb_train_0[i][j] = shatt_mbed[i][j] * weights[i][j];
        }
    }

    // Print checkpoint
    printf("Checkpoint: ");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%lf ", shatt_emb_train_0[i][j]);
        }
        printf("\n");
    }

    // Create bias data and write to file
    double bias[1][6];
    srand(time(NULL));
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 6; j++) {
            bias[i][j] = (double)rand() / RAND_MAX * 0.98 + 0.01;
        }
    }

    fp = fopen("bias.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 6; j++) {
            fprintf(fp, "%lf ", bias[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    // Multiply shatt_emb_train_0 and bias
    double shatt_emb_train_1[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            shatt_emb_train_1[i][j] = shatt_emb_train_0[i][j] * 
bias[0][j];
        }
    }

    // Print checkpoint and write to file
    printf("Checkpoint: ");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%lf ", shatt_emb_train_1[i][j]);
        }
        printf("\n");
    }

    fp = fopen("shatt_emb_train.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fprintf(fp, "%lf ", shatt_emb_train_1[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    return 0;
}

