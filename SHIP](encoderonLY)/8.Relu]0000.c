#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Define RELU activation function
double relu(double x) {
    return (x > 0) ? x : 0;
}

int main() {
    // Read linlay[6][6] from "linlay.txt"
    FILE *fp = fopen("linlay.txt", "r");
    double linlay[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fscanf(fp, "%lf", &linlay[i][j]);
        }
    }
    fclose(fp);

    // Apply RELU to linlay
    double relu_linlay[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            relu_linlay[i][j] = relu(linlay[i][j]);
        }
    }

    // Print RELU result as a checkpoint
    printf("RELU linlay:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%lf ", relu_linlay[i][j]);
        }
        printf("\n");
    }

    // Read shatt_mbed[6][6] from "shatt_mbed.txt"
    fp = fopen("shatt_mbed.txt", "r");
    double shatt_mbed[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fscanf(fp, "%lf", &shatt_mbed[i][j]);
        }
    }
    fclose(fp);

    // Add relu_linlay and shatt_mbed as encOut[6][6]
    double encOut[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            encOut[i][j] = relu_linlay[i][j] + shatt_mbed[i][j];
        }
    }

    // Print result as a checkpoint
    printf("encOut:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%lf ", encOut[i][j]);
        }
        printf("\n");
    }

    // Normalize encOut using row-wise mean and standard deviation
    double sum[6], mean[6], std_dev[6];
    for (int i = 0; i < 6; i++) {
        sum[i] = 0.0;
        for (int j = 0; j < 6; j++) {
            sum[i] += encOut[i][j];
        }
        mean[i] = sum[i] / 6.0;
    }

    for (int i = 0; i < 6; i++) {
        std_dev[i] = 0.0;
        for (int j = 0; j < 6; j++) {
            std_dev[i] += pow(encOut[i][j] - mean[i], 2);
        }
        std_dev[i] = sqrt(std_dev[i] / 5.0); // calculate standard deviation
    }

    double norm_encOut[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            norm_encOut[i][j] = (encOut[i][j] - mean[i]) / std_dev[i];
        }
    }

    // Print normalized result as a checkpoint
    printf("Normalized encOut:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%lf ", norm_encOut[i][j]);
        }
        printf("\n");
    }

    // Write result to "encOut.txt"
    fp = fopen("encOut.txt", "w");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fprintf(fp, "%lf ", norm_encOut[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}

