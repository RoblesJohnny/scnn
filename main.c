#include "scnn.h"

int main()
{
    float x[] = {1, 1};
    float y[] = {1};

    scnn_neural_network_t neural_net = scnn_create();
    scnn_add_layer(neural_net, 2, 2, relu);
    scnn_add_layer(neural_net, 2, 2, relu);
    scnn_fit(neural_net, x, y, 2);
    scnn_summary(neural_net);
    scnn_destroy(neural_net);

    return 0;
}