#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 6

int main() {
    FILE *fp1 = fopen("shatt+.txt", "r");
    FILE *fp2 = fopen("resultant.txt", "r");
    FILE *fout = fopen("shatt_mbed.txt", "w");

    double shatt_mbed[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fscanf(fp1, "%lf ", &shatt_mbed[i][j]);
            fscanf(fp2, "%lf ", &shatt_mbed[i][j]);
        }
    }

    // Compute row-wise mean and standard deviation
    double means[SIZE];
    double std_devs[SIZE];
    for (int i = 0; i < SIZE; i++) {
        double sum = 0.0;
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            sum += shatt_mbed[i][j];
            count++;
        }
        means[i] = sum / count;

        sum = 0.0;
        for (int j = 0; j < SIZE; j++) {
            sum += pow(shatt_mbed[i][j] - means[i], 2);
        }
        std_devs[i] = sqrt(sum / count);
    }

    // Normalize the matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            shatt_mbed[i][j] -= means[i];
            shatt_mbed[i][j] /= std_devs[i];
        }
    }

    // Write the normalized matrix to file
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(fout, "%lf ", shatt_mbed[i][j]);
            printf("%lf ", shatt_mbed[i][j]);
        }
        fprintf(fout, "\n");
        printf("\n");
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fout);

    return 0;
}

