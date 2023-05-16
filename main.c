#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_NN_LAYERS 10

typedef enum activation_function_t {
    relu,
    sigmoid
} activation_function_t;

typedef struct neuron_t 
{
    float value;
    size_t weigths_size;
    float weights[];
} neuron_t;
//Defines a layer of a neural network
typedef struct layer_t
{
    size_t dimension;
    activation_function_t activation_function;
    neuron_t *neuron[];
} layer_t;

typedef struct neural_net_t
{
         //A maximum of 10 layers per neural network
    //bool (*add_layer) (struct neural_net_t *nn, struct layer_t *layer); //Pointer to a function to add layers to the neural network
    size_t size;
    layer_t layers[];
} neural_net_t;

bool scnn_neural_net_layer_add(neural_net_t *nn, layer_t *layer)
{
    return true;
}

// Creates a neural network
neural_net_t scnn_neural_network_create()
{
    neural_net_t neural_net;
    //neural_net.add_layer = scnn_neural_net_layer_add;
    return neural_net;
}


// Creates a layer of a neural network
layer_t *scnn_layer_create(size_t size)
{ 
    layer_t *layer = (layer_t *) malloc(sizeof(layer_t) + size * sizeof(double *));
    layer->dimension = size;
    return layer;
}

//Generates random numbers between 0 and 1 to initialize weights 
double scnn_weights_init()
{
    return ((double) rand() / (double)RAND_MAX); 
}

//Multiplies two layers and returns a pointer to the resulting layer
layer_t *scnn_layer_multiply(layer_t *l1, layer_t *l2)
{
    layer_t *result = scnn_layer_create(l1->size);

    for (size_t i = 0; i < l1->size; i++)
    {
        result->nodes[i] = l1->nodes[i] * l2->nodes[i];
    }
    return result;
}

void scnn_neural_network_train(neural_net_t *neural_net, int epochs)
{
    for (size_t i = 0; i < epochs; i++)
    {
        for (size_t j = 0; j < MAX_NN_LAYERS; j++)
        {
            for (size_t k = 0; k < neural_net->layers[j].size; i++)
            {
                printf("%lf\n", neural_net->layers[j].nodes[k]);
            }
        }
    }
}

int main()
{
    srand((unsigned) time(NULL));
    size_t n = 1;
    size_t m = 1;

    layer_t *layer1 = scnn_layer_create(n);
    layer_t *layer2 = scnn_layer_create(m);

    for (size_t i = 0; i < 11; i++)
    {
        layer1->nodes[i] = scnn_weights_init();
        layer2->nodes[i] = scnn_weights_init();
    }

    layer_t *result = scnn_layer_multiply(layer1, layer2);

    for (size_t i = 0; i < n; i++)
    {
        printf("%lf\t%lf\t%lf\n", layer1->nodes[i], layer2->nodes[i], result->nodes[i]);
    }
    
    free(layer1);    
    free(layer2);
    free(result);

    return 0;
}