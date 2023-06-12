#include "scnn.h"

typedef struct SCNN_LAYER_T
{
    size_t dimension;
    size_t input_shape;
    char layer_name[10];
    activation_function_t activation_function;
    float bias;
    MATRIX_T weights;
} SCNN_LAYER_T;

struct SCNN_NEURAL_NETWORK
{
    SCNN_LAYER_T layers[MAX_LAYERS];
} 


// typedef struct scnn_neuron_t
// {
//     float value;
//     size_t weights_size;
//     float weights[];
// } scnn_neuron_t;

// typedef struct scnn_layer_t
// {
//     activation_function_t activation_function;
//     float bias;
//     size_t dimension;
//     size_t input_shape;
//     scnn_neuron_t *neuron[];
// } scnn_layer_t;

// struct scnn_neural_network_t
// {
//     scnn_layer_t *layers[MAX_LAYERS]; //Max 10 layers in a NN
//     //void (*add_layer) (struct scnn_neural_network_t *self, size_t dimension, size_t input_shape);
// };

//Generates random numbers between 0 and 1 to initialize weights 
double scnn_neuron_weights_init()
{
    return ((double) rand() / (double)RAND_MAX); 
}

// scnn_neuron_t *scnn_neuron_create(size_t weights_size)
// {
//     scnn_neuron_t *neuron = (scnn_neuron_t *) malloc(sizeof(scnn_neuron_t) + weights_size * sizeof(float));
//     neuron->weights_size = weights_size;
//     neuron->value = 0;

//     //Weights random initialization
//     for (size_t i = 0; i < weights_size; i++)
//     {
//         neuron->weights[i] = scnn_neuron_weights_init();
//     }
    
//     return neuron;
// }

SCNN_LAYER_T scnn_layer_create(size_t dimension, size_t input_shape, activation_function_t activation_function)
{
    //scnn_layer_t *layer = (scnn_layer_t *) malloc(sizeof(scnn_layer_t) + dimension * sizeof(scnn_neuron_t *));
    SCNN_LAYER_T layer;
    layer.dimension = dimension;
    layer.activation_function = activation_function;
    layer.input_shape = input_shape;
    layer.bias = scnn_neuron_weights_init();
    layer.weights = matrix_create(dimension, input_shape); //TODO: Check if this works
    
    return layer;
}

//Creates an input layer to store the input dataset
//Warning: Caller must free the returned pointer
scnn_input_layer_t *scnn_input_layer_create(size_t size)
{
    scnn_input_layer_t *input_layer = (scnn_input_layer_t *) malloc(sizeof(scnn_layer_t) + size * sizeof(float));
    input_layer->size = size;

    return input_layer;
}

void scnn_add_layer(SCNN_NEURAL_NETWORK_T nn, size_t dimension, size_t input_shape, activation_function_t activation_function)
{
    for (size_t i = 0; i < MAX_LAYERS; i++)
    {
        if (neural_net->layers[i] == NULL)
        {   
            neural_net->layers[i] = scnn_layer_create(dimension, input_shape, activation_function);
            break;
        }
    }
        
}

SCNN_NEURAL_NETWORK_T scnn_create()
{
    SCNN_NEURAL_NETWORK_T neural_net;
    srand((unsigned) time(NULL));
    
    return neural_net;
}

void scnn_destroy(scnn_neural_network_t neural_network)
{
    size_t i =0;
    while (neural_network->layers[i] != NULL)
    {
        for (size_t j = 0; j < neural_network->layers[i]->dimension; j++)
        {
            free(neural_network->layers[i]->neuron[j]);
        }
        free(neural_network->layers[i]);
        i++;
    }

    free(neural_network);
}

// Prints the summary of the composition of a neural network
void scnn_summary(scnn_neural_network_t nn)
{
    size_t i = 0;
    while (nn->layers[i] != NULL)
    {
        printf("Layer dimension: %lu\n", nn->layers[i]->dimension);

        for (size_t j = 0; j < nn->layers[i]->dimension; j++)
        {
            printf("neuron value: %f\n", nn->layers[i]->neuron[j]->value);
            for (size_t k = 0; k < nn->layers[i]->neuron[j]->weights_size; k++)
            {
                printf("neuron weights %f\n", nn->layers[i]->neuron[j]->weights[k]);
            }
        }
        i++;
    }
}

//reLu activation function
float scnn_relu_activation_function(float input) 
{ 
    if (input > 0)
    {
        return input;
    } else 
    {
        return 0;
    }
}

//Training process of a neural network
//TODO how to move the result of a layer as the input of the next layer
void scnn_fit(scnn_neural_network_t nn, scnn_input_layer_t *x_input, float y_output[], size_t epochs)
{
    //Duplicates the input layer
    scnn_input_layer_t *working_input_layer = scnn_input_layer_create(x_input->size);
    
    for (size_t i = 0; i < x_input->size; i++)
    {
        working_input_layer->input[i] = x_input->input[i];
    }
    
    //Forward propagation
    for (size_t i = 0; i < epochs; i++)
    {
        size_t j = 0;
        while (nn->layers[j] != NULL)
        {
            for (size_t k = 0; k < nn->layers[j]->dimension; k++)
            {
                for (size_t l = 0; l < x_input->size; l++)
                {
                    nn->layers[j]->neuron[k]->value += (working_input_layer->input[l] * nn->layers[j]->neuron[k]->weights[l]); 
                    printf("input value: %f\tweight: %f\tproduct: %f\n", working_input_layer->input[l], nn->layers[j]->neuron[k]->weights[l],  working_input_layer->input[l] * nn->layers[j]->neuron[k]->weights[l]);
                } 
                
                //Add the bias to the neuron
                nn->layers[j]->neuron[k]->value += nn->layers[j]->bias;

                //Calls the activation function for this neuron
                switch (nn->layers[j]->activation_function)
                {
                case relu:
                {
                    nn->layers[j]->neuron[k]->value = scnn_relu_activation_function(nn->layers[j]->neuron[k]->value);
                    break;
                }
                default:
                    break;
                }

                printf("neuron value: %f\t\n", nn->layers[j]->neuron[k]->value);
            }

            //Copy the calculated layer to the working input layer
            free(working_input_layer);
            working_input_layer = scnn_input_layer_create(nn->layers[j]->dimension);

            for (size_t m = 0; m < nn->layers[j]->dimension; m++)
            {
                working_input_layer->input[m] = nn->layers[j]->neuron[m]->value;
            }
            j++;
        }
        //free(working_input_layer);
    }

    // Backpropagation
}

float scnn_loss_function()
{
    
    return 0;
}






void scnn_fit2(SCNN_NEURAL_NETWORK nn, float x[], float y[], size_t epochs)
{

}

