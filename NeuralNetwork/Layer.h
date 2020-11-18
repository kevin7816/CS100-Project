#ifndef __LAYER_H__
#define __LAYER_H__

#include "Neuron.h"
#include <iostream>

class Layer {
public:
    Neuron* neurons;
    unsigned num_neurons;

    float ** adjacency_matrix;
    unsigned rows;
    unsigned cols;

    Layer(unsigned num_neurons): num_neurons(num_neurons) {
        init_neurons();
    }
    Layer(unsigned num_neurons, unsigned rows, unsigned cols): num_neurons(num_neurons), rows(rows), cols(cols) {
        init_neurons();

        init_weights();
    }

    ~Layer() {
        delete [] neurons;
        for (unsigned i = 0; i < rows; ++i) {
            delete [] adjacency_matrix[i];
        }
        delete [] adjacency_matrix;
    }
private:
    float fRand(float fMin, float fMax) {
        float f = (float)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
    void init_neurons() {
        neurons = new Neuron[num_neurons];
        for (unsigned i = 0; i < num_neurons; ++i) {
            Neuron new_neuron;
            new_neuron.bias = fRand(-1,1);
            neurons[i] = new_neuron;
            std::cout << "bias: " << neurons[i].bias << std::endl;
        }
    }
    void init_weights() {
        adjacency_matrix = new float*[rows];
        for (unsigned i = 0; i < rows; ++i) {
            adjacency_matrix[i] = new float[cols];
            for (unsigned j = 0; j < cols; ++j) {
                adjacency_matrix[i][j] = fRand(-1,1);
                std::cout << adjacency_matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};

#endif
