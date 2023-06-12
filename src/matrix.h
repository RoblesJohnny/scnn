#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//****************************************************************************
// Structures
//****************************************************************************

// MATRIX_T structure
typedef struct {
    int rows;
    int cols;
    float *data;
} MATRIX_T;

//****************************************************************************
// MATRIX_T functions declaration
//****************************************************************************
MATRIX_T matrix_create(int rows, int cols);
void matrix_print(MATRIX_T m);
void matrix_randomize(MATRIX_T m);
void matrix_add(MATRIX_T c, MATRIX_T a, MATRIX_T b);
void matrix_multiply(MATRIX_T m3, MATRIX_T m1, MATRIX_T m2);
void matrix_destroy(MATRIX_T m);

#endif