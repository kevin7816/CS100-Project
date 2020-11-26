#ifndef __NETWORK_HANDLER_H__
#define __NETWORK_HANDLER_H__

#include "NeuralNetwork.h"

class NetworkHandler {
private:
    NetworkParams network_params;
    float mutation_rate;
    unsigned generation_size;

public:
    NetworkHandler(unsigned inputs, unsigned outputs, unsigned hidden_layers, unsigned hidden_layer_size, float mutation_rate, unsigned generation_size): mutation_rate(mutation_rate), generation_size(generation_size) {
        network_params.input = input;
        network_params.output = output;
        network_params.hidden_layers = hidden_layers;
        network_params.hidden_layer_size = hidden_layer_size;
    }
}

#endif
