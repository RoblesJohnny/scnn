#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAX_LAYERS 10

typedef struct neuron_t
{
    float value;
    size_t weights_size;
    float weights[];
} neuron_t;

typedef struct layer_t
{
    size_t dimension;
    size_t input_shape;
    neuron_t *neuron[];
} layer_t;

typedef struct neural_network_t
{
    layer_t *layers[MAX_LAYERS]; //Max 10 layers in a NN
    void (*add_layer) (struct neural_network_t *self, size_t dimension, size_t input_shape);
} neural_network_t;


//Generates random numbers between 0 and 1 to initialize weights 
double scnn_weights_init()
{
    return ((double) rand() / (double)RAND_MAX); 
}

neuron_t *create_neuron(size_t weights_size)
{
    neuron_t *neuron = (neuron_t *) malloc(sizeof(neuron_t) + weights_size * sizeof(float));
    neuron->weights_size = weights_size;
    neuron->value = 0;

    //Weights random initialization
    for (size_t i = 0; i < weights_size; i++)
    {
        neuron->weights[i] = scnn_weights_init();
    }
    
    return neuron;
}


layer_t *create_layer(size_t dimension, size_t input_shape)
{
    layer_t *layer = (layer_t *) malloc(sizeof(layer_t) + dimension * sizeof(neuron_t *));
    layer->dimension = dimension;
    layer->input_shape = input_shape;
    for (size_t i = 0; i < dimension; i++)
    {
        layer->neuron[i] = create_neuron(layer->input_shape);
    }
    
    return layer;
}

void add_layer(neural_network_t *neural_net, size_t dimension, size_t input_shape)
{
    for (size_t i = 0; i < MAX_LAYERS; i++)
    {
        if (neural_net->layers[i] == NULL)
        {
            neural_net->layers[i] = create_layer(dimension, input_shape);
            break;
        }
    }
        
}

neural_network_t create_neural_network()
{
    neural_network_t neural_net;
    neural_net.add_layer = add_layer;

    //initialize layer array
    for (size_t i = 0; i < MAX_LAYERS; i++)
    {
        neural_net.layers[i] = NULL;
    }
    
    return neural_net;
}

int main()
{
    size_t dimension = 6;
    size_t input_shape = 4;

    srand((unsigned) time(NULL));

    neural_network_t neural_net = create_neural_network();
    neural_net.add_layer(&neural_net, 6, 4);
    neural_net.add_layer(&neural_net, 8, 6);

    for (size_t x = 0; x < 2; x++) //Change for MAX_LAYERS but before fixing segmentation fault
    {
        printf("Layer dimension: %lu\n", neural_net.layers[x]->dimension);

        for (size_t i = 0; i < neural_net.layers[x]->dimension; i++)
        {
            printf("neuron value: %f\n", neural_net.layers[x]->neuron[i]->value);
            for (size_t j = 0; j < neural_net.layers[x]->neuron[i]->weights_size; j++)
            {
                printf("neuron weights %f\n", neural_net.layers[x]->neuron[i]->weights[j]);
            }
        }
    }

    //TO DO: Free all the resources with a destroy method.

    return 0;
}