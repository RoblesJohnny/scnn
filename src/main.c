#include "scnn.h"

int main()
{
    scnn_input_layer_t *x = scnn_input_layer_create(2);
    x->input[0] = 1;
    x->input[1] = 1;

    SCNN_NEURAL_NETWORK_T neural_net = scnn_create();
    

    // float y[] = {1};

    // scnn_neural_network_t neural_net = scnn_create();
    // scnn_add_layer(neural_net, 2, 2, relu);
    // scnn_add_layer(neural_net, 2, 2, relu);
    // scnn_fit(neural_net, x, y, 5);
    // scnn_summary(neural_net);
    // scnn_destroy(neural_net);
    // free(x);
    return 0;
}