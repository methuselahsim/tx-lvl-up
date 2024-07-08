#include <stdio.h>

int main() {
    int i, j;
    FILE *fp_query_embeds = fopen("query_embeds.txt", "r");
    FILE *fp_pos_encoding = fopen("positional_encoding.txt", "r");
    FILE *fp_resultant = fopen("resultant.txt", "w");

    if (fp_query_embeds == NULL || fp_pos_encoding == NULL || fp_resultant == 
NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    float query_values[6][6];
for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
        float val1, val2;
        fscanf(fp_query_embeds, "%f ", &val1);
        fscanf(fp_pos_encoding, "%f ", &val2);
        query_values[i][j] = val1 + val2; // Add the values
    }
}


for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
        fprintf(fp_resultant, "%f ", query_values[i][j]);
    }
    fprintf(fp_resultant, "\n");
}


    fclose(fp_query_embeds);
    fclose(fp_pos_encoding);
    fclose(fp_resultant);

    return 0;
}

