#include <stdio.h>
#include "matrix.h"
#include <math.h>

typedef struct neural_network
{
    MATRIX_T a0;
    MATRIX_T w1;
    MATRIX_T b1;
    MATRIX_T a1;
    MATRIX_T w2;
    MATRIX_T b2;
    MATRIX_T a2;
} neural_network;

neural_network neural_network_create()
{
    //Initialize random number generator
    srand(time(0));

    //Create neural network
    struct neural_network nn;
    nn.a0 = matrix_create(2, 1);
    nn.w1 = matrix_create(2, 2);
    matrix_randomize(nn.w1);
    nn.b1 = matrix_create(2, 1);
    matrix_randomize(nn.b1);
    nn.a1 = matrix_create(2, 1);
    nn.w2 = matrix_create(1, 2);
    matrix_randomize(nn.w2);
    nn.b2 = matrix_create(1, 1);
    matrix_randomize(nn.b2);
    nn.a2 = matrix_create(1, 1);
    return nn;
}

//RELU activation function
 float relu(float x)
 {
        if (x < 0)
        {
            return 0;
        }
        else
        {
            return x;
        }
 }

//Sigmoid activation function
 float sigmoid(float x)
 {
     return 1 / (1 + exp(-x));
 }

void activate_layer(MATRIX_T nn, float (*activation_function)(float))
{
    for (int i = 0; i < nn.rows * nn.cols; i++)
    {
        nn.data[i] = activation_function(nn.data[i]);
    }
}

void forward_pass(neural_network nn)
{
    matrix_multiply(nn.a1, nn.w1, nn.a0);
    matrix_add(nn.a1, nn.a1, nn.b1);
    activate_layer(nn.a1, relu);
    matrix_multiply(nn.a2, nn.w2, nn.a1);
    matrix_add(nn.a2, nn.a2, nn.b2);
    activate_layer(nn.a2, sigmoid);
}

int main()
{
    neural_network nn = neural_network_create();
    nn.a0.data[0] = 1;
    nn.a0.data[1] = 1;
    forward_pass(nn);
    matrix_print(nn.a2);
    return 0;
}