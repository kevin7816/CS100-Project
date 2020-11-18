#ifndef __NEURON_H__
#define __NEURON_H__

#include <iostream>

struct Neuron {
    float activation;
    float bias;

    Neuron(): activation(0) {}
};

#endif
