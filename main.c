#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

typedef struct layer_t
{
    size_t size;
    double nodes[];

} layer_t;

// Creates a flexible member array for each layer
layer_t *scnn_layer_create(size_t size)
{ 
    layer_t *layer = (layer_t *) malloc(sizeof(layer_t) + size * sizeof(double));
    layer->size = size;
    return layer;
}

//Generates random numbers between 0 and 1 to initialize weights 
double scnn_weights_init()
{
    return ((double) rand() / (double)RAND_MAX); 
}

layer_t *multiply(layer_t *l1, layer_t *l2)
{
    layer_t *result = scnn_layer_create(l1->size);

    for (size_t i = 0; i < l1->size; i++)
    {
        result->nodes[i] = l1->nodes[i] * l2->nodes[i];
    }
    return result;
}

int main()
{
    srand((unsigned) time(NULL));
    size_t n = 10;
    size_t m = 10;

    layer_t *layer1 = scnn_layer_create(n);
    layer_t *layer2 = scnn_layer_create(m);

    for (size_t i = 0; i < 11; i++)
    {
        layer1->nodes[i] = scnn_weights_init();
        layer2->nodes[i] = scnn_weights_init();
    }

    layer_t *result = multiply(layer1, layer2);

    for (size_t i = 0; i < n; i++)
    {
        printf("%lf\t%lf\t%lf\n", layer1->nodes[i], layer2->nodes[i], result->nodes[i]);
    }
    
    free(layer1);    
    free(layer2);
    free(result);

    return 0;
}