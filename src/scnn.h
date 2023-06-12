#ifndef _SCNN_H_
#define _SCNN_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

#define MAX_LAYERS 10

typedef enum activation_function_t {
    sigmoid,
    relu
} activation_function_t;

//Input layer structure
typedef struct scnn_input_layer_t
{
    size_t size;
    float input[];
} scnn_input_layer_t;

//Opaque pointer for hiding implementation details
typedef struct SCNN_NEURAL_NETWORK *SCNN_NEURAL_NETWORK_T;

/******************************************************************************************************
* Functions declaration
*******************************************************************************************************/
scnn_neural_network_t scnn_create();
void scnn_destroy(scnn_neural_network_t nn);
void scnn_add_layer(scnn_neural_network_t neural_net, size_t dimension, size_t input_shape, activation_function_t activation_function);
void scnn_summary(scnn_neural_network_t nn);
void scnn_fit(scnn_neural_network_t nn, scnn_input_layer_t *x_input, float y_output[], size_t epochs);
void scnn_fit2()
scnn_input_layer_t *scnn_input_layer_create(size_t size);
// int scnn_save(scnn_neural_network_t nn, char *path);
// scnn_neural_network_t scnn_load(char *path);

#endif

