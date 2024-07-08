#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define ROW_SIZE 6
#define COL_SIZE 4

int main() {
    double q[ROW_SIZE][COL_SIZE], k[ROW_SIZE][COL_SIZE], 
v[ROW_SIZE][COL_SIZE];
    double tp[COL_SIZE][ROW_SIZE];

    FILE *fp = fopen("encodings.txt", "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    int i, j;

    // Read Q matrix
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < COL_SIZE; j++) {
            if (fscanf(fp, "%lf", &q[i][j]) != 1) {
                perror("Error reading file");
                return 1;
            }
        }
    }

    // Read K matrix
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < COL_SIZE; j++) {
            if (fscanf(fp, "%lf", &k[i][j]) != 1) {
                perror("Error reading file");
                return 1;
            }
        }
    }

    // Read V matrix
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < COL_SIZE; j++) {
            if (fscanf(fp, "%lf", &v[i][j]) != 1) {
                perror("Error reading file");
                return 1;
            }
        }
    }

    fclose(fp);

    // Transpose the K matrix
    for (i = 0; i < COL_SIZE; i++) {
        for (j = 0; j < ROW_SIZE; j++) {
            tp[i][j] = k[j][i];
            printf("%f ", tp[i][j]);
        }
        printf("\n");
    }

    // Calculate Query-Key Scaled Dot Product
    double pro[ROW_SIZE][ROW_SIZE], scaledPro[ROW_SIZE][ROW_SIZE];
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < ROW_SIZE; j++) {
            double sum = 0;
            for (int k = 0; k < COL_SIZE; k++) {
                sum += q[i][k] * tp[k][j];
            }
            pro[i][j] = sum;
        }
    }

    // Scale the resultant matrix
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < ROW_SIZE; j++) {
            scaledPro[i][j] = pro[i][j] / ROW_SIZE;
        }
    }

    // Print the result as a checkpoint
    printf("Query-Key Scaled Dot Product (Scaled):\n");
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < ROW_SIZE; j++) {
            printf("%f ", scaledPro[i][j]);
        }
        printf("\n");
    }
    
      // Apply Softmax
    double sum, expSum;
    double softPro[ROW_SIZE][ROW_SIZE];

    
    for (int i = 0; i < ROW_SIZE; i++) {
    double maxVal = -INFINITY;
    for (int j = 0; j < ROW_SIZE; j++) {
        maxVal = fmax(maxVal, scaledPro[i][j]);
    }
    sum = 0.0;
    for (int j = 0; j < ROW_SIZE; j++) {
        expSum = exp(scaledPro[i][j] - maxVal);
        sum += expSum;
    }
    for (int j = 0; j < ROW_SIZE; j++) {
        softPro[i][j] = exp(scaledPro[i][j] - maxVal) / sum;
    }
}

    

    // Print the Softmax result
    printf("Softmax Query-Key Scaled Dot Product (Scaled):\n");
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            printf("%f ", softPro[i][j]);
        }
        printf("\n");
    }



   // Matrix multiplication with v matrix
    double matMult[ROW_SIZE][COL_SIZE];
    for (i = 0; i < ROW_SIZE; i++) {
        for (j = 0; j < COL_SIZE; j++) {
            double sum = 0;
            for (int k = 0; k < ROW_SIZE; k++) {
                sum += scaledPro[i][k] * v[k][j];
            }
            matMult[i][j] = sum;
        }
    }

    // Print the matrix multiplication result
    printf("Matrix Multiplication Result:\n");
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < COL_SIZE; j++) {
            printf("%f ", matMult[i][j]);
        }
        printf("\n");
    }

 

    // Generate random linear weights matrix
    double weights[4][6];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            weights[i][j] = (double)rand() / RAND_MAX * 0.98 + 0.01;
        }
    }

    // Multiply the matrix with the linear weights
    double multran[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            double sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += matMult[i][k] * weights[k][j];
            }
            multran[i][j] = sum;
        }
    }

    // Write the matrix multiplication result to file
    FILE *fp2 = fopen("shatt+.txt", "w");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            fprintf(fp2, "%f ", multran[i][j]);
        }
        fprintf(fp2, "\n");
    }
    fclose(fp2);
    
     // Print the matrix multiplication result
    printf("shatt+ Result:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%f ", multran[i][j]);
        }
        printf("\n");
    }

    return 0;


}


