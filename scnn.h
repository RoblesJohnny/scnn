#ifndef _SCNN_H_
#define _SCNN_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


typedef enum activation_function_t {
    sigmoid,
    relu
} activation_function_t;

//Opaque pointer for hiding implementation details
typedef struct scnn_neural_network_t *scnn_neural_network_t;

//Functions declaration
scnn_neural_network_t scnn_create();
void scnn_destroy(scnn_neural_network_t nn);
void scnn_add_layer(scnn_neural_network_t neural_net, size_t dimension, size_t input_shape, activation_function_t activation_function);
void scnn_summary(scnn_neural_network_t nn);
void scnn_fit(scnn_neural_network_t nn, float x_input[], float y_output[], size_t epochs);

#endif

