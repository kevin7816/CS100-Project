#ifndef __LAYER_H__
#define __LAYER_H__

#include "Neuron.h"
#include <random>
#include <iostream>

class Layer {
public:
    Neuron* neurons;
    unsigned num_neurons;

    float ** adjacency_matrix;
    unsigned rows;
    unsigned cols;

    Layer(unsigned num_neurons): num_neurons(num_neurons) {
        neurons = new Neuron[num_neurons];
        for (unsigned i = 0; i < num_neurons; ++i) {
            Neuron new_neuron;
            neurons[i] = new_neuron;
        }
    }
    Layer(unsigned num_neurons, unsigned rows, unsigned cols): num_neurons(num_neurons), rows(rows), cols(cols) {
        float lower_bound = -1;
        float upper_bound = 1;
        std::uniform_real_distribution<float> unif(lower_bound, upper_bound);
        std::default_random_engine re;

        neurons = new Neuron[num_neurons];
        for (unsigned i = 0; i < num_neurons; ++i) {
            Neuron new_neuron;
            neurons[i] = new_neuron;
        }

        adjacency_matrix = new float*[rows];
        for (unsigned i = 0; i < rows; ++i) {
            adjacency_matrix[i] = new float[cols];
            for (unsigned j = 0; j < cols; ++j) {
                adjacency_matrix[i][j] = unif(re);
                std::cout << adjacency_matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    ~Layer() {
        delete [] neurons;
        for (unsigned i = 0; i < rows; ++i) {
            delete [] adjacency_matrix[i];
        }
        delete [] adjacency_matrix;
    }
};

#endif
