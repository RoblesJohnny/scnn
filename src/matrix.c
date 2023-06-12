#include "matrix.h"

//Creates a matrix with the given number of rows and columns
MATRIX_T matrix_create(int rows, int cols) {
    MATRIX_T m;
    m.rows = rows;
    m.cols = cols;
    m.data = (float *) malloc(rows * cols * sizeof(float));
    return m;
}

//Generates a random number between 0 and 1
float random_number() {
    return (float) rand() / (float) RAND_MAX;
}

//Prints the matrix contents
void matrix_print(MATRIX_T m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            printf("%f ", m.data[i * m.cols + j]);
        printf("\n");
    }
}

//Frees the memory allocated to the matrix
void matrix_destroy(MATRIX_T m) {
    free(m.data);
}

//Initializes the matrix with random values
void matrix_randomize(MATRIX_T m) {
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            m.data[i * m.cols + j] = random_number();
}

//Multiplies two matrices and returns the result
void matrix_multiply(MATRIX_T m3, MATRIX_T m1, MATRIX_T m2) {
    if (m1.cols != m2.rows)
    {
        printf("Error: MATRIX_T dimensions do not match!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m1.rows; i++)
        for (int j = 0; j < m2.cols; j++) {
            float sum = 0;
            for (int k = 0; k < m1.cols; k++)
                sum += m1.data[i * m1.cols + k] * m2.data[k * m2.cols + j];
            m3.data[i * m3.cols + j] = sum;
        }
}

//write a function to load a csv file into a matrix
MATRIX_T matrix_load_from_csv(char *filename) {
    FILE *fp = fopen(filename, "r");
    char line[1024];
    int i = 0;
    int j = 0;
    MATRIX_T m;
    m.rows = 0;
    m.cols = 0;
    m.data = NULL;
    while (fgets(line, 1024, fp)) {
        j = 0;
        char *tmp = strdup(line);
        char *token = strtok(tmp, ",");
        while (token) {
            m.data = realloc(m.data, sizeof(float) * (i * m.cols + j + 1));
            m.data[i * m.cols + j] = atof(token);
            token = strtok(NULL, ",");
            j++;
        }
        if (m.cols == 0)
            m.cols = j;
        i++;
        free(tmp);
    }
    m.rows = i;
    fclose(fp);
    return m;
}

//Write a function to save a matrix to a csv file
void matrix_save_to_csv(char *filename, MATRIX_T m) {
    FILE *fp = fopen(filename, "w");
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            fprintf(fp, "%f,", m.data[i * m.cols + j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

//Write a function to add two matrices
void matrix_add(MATRIX_T m3, MATRIX_T m1, MATRIX_T m2) {
    if (m1.rows != m2.rows || m1.cols != m2.cols)
    {
        printf("Error: MATRIX_T dimensions do not match!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m1.rows; i++)
        for (int j = 0; j < m1.cols; j++)
            m3.data[i * m3.cols + j] = m1.data[i * m1.cols + j] + m2.data[i * m2.cols + j];
}   