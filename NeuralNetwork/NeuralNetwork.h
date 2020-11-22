#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include "Matrix.h"
#include <iostream>

class NeuralNetwork {
private:
    unsigned num_layers;
    unsigned inputs;
    unsigned outputs;
    unsigned hidden_layer_size;

    float*** adjacency_matrices; //array of 2d arrays

    float** biases;
    float** activations;

public:
    //note: at least 1 hidden layer is required;
    NeuralNetwork(unsigned inputs, unsigned outputs, unsigned hidden_layers, unsigned hidden_layer_size): inputs(inputs),  outputs(outputs), hidden_layer_size(hidden_layer_size) {
        num_layers = hidden_layers + 2;

        //initializing the weights in the adjacency matrices
        adjacency_matrices = new float**[num_layers]; //all layers have a adjacency matrix except for input layer
        for (unsigned index = 0; index < num_layers-1; ++index) {
            if (index == 0) { //first adjacency_matrix is under the second layer
                adjacency_matrices[index] = new float*[hidden_layer_size];
                init_layer(index, hidden_layer_size, inputs);
            }

            else if (index == num_layers-2) { //last adjacency matrix on the output layer
                adjacency_matrices[index] = new float*[outputs];
                init_layer(index, outputs, hidden_layer_size);
            }

            else { // hidden layers connected to hidden layers
                adjacency_matrices[index] = new float*[hidden_layer_size];
                init_layer(index, hidden_layer_size, hidden_layer_size);
            }
        }

        //initializing the biases and activations
        biases = new float*[num_layers];
        activations = new float*[num_layers];
        for (unsigned i = 0; i < num_layers; ++i) {
            if (i == 0) { //input layer
                biases[i] = new float[inputs];
                activations[i] = new float[inputs];
                init_nodes(i, inputs);
            }
            else if (i == num_layers - 1) { //output layer
                biases[i] = new float[outputs];
                activations[i] = new float[outputs];
                init_nodes(i, outputs);
            }
            else { //hidden_layers
                biases[i] = new float[hidden_layer_size];
                activations[i] = new float[hidden_layer_size];
                init_nodes(i, hidden_layer_size);
            }
        }



    }

    void forward_propagation() {
        for (unsigned index = 1; index < num_layers; ++index) {
            float* solution;
            unsigned size;
            if (index == 1) { //input layer -> hidden layer
                size = hidden_layer_size;
                activations[index] = Matrix::multiply(adjacency_matrices[index-1], activations[index-1], hidden_layer_size, inputs);
            }
            else if (index == num_layers-1) { //hidden layer -> output layer
                size = outputs;
                activations[index] = Matrix::multiply(adjacency_matrices[index-1], activations[index-1], outputs, hidden_layer_size);
            }
            else { //hidden layer -> hidden layer
                size = hidden_layer_size;
                activations[index] = Matrix::multiply(adjacency_matrices[index-1], activations[index-1], hidden_layer_size, hidden_layer_size);
            }

            for (unsigned i = 0; i < size; ++i) {
                activations[index][i] += biases[index][i];
                activations[index][i] = ReLU(activations[index][i]);
            }
        }
    }

    void print_activations() {
        std::cout << "activations:\n";
        for(unsigned i = 0; i < num_layers; ++i) {
            unsigned size = hidden_layer_size;
            if ( i == 0) {
                size = inputs;
            }
            else if (i == num_layers-1) {
                size = outputs;
            }
            for (unsigned j = 0; j < size; ++j) {
                std::cout<< activations[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    void print_biases() {
        std::cout << "biases:\n";
        for(unsigned i = 0; i < num_layers; ++i) {
            unsigned size = hidden_layer_size;
            if ( i == 0) {
                size = inputs;
            }
            else if (i == num_layers-1) {
                size = outputs;
            }
            for (unsigned j = 0; j < size; ++j) {
                std::cout<< biases[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    void print_weights() {
        std::cout << "weights:-----------------------------------------------------------------------------------------------------------------------------------\n";
        for (unsigned index = 0; index < num_layers-1; ++index) {
            unsigned rows = hidden_layer_size;
            unsigned cols = hidden_layer_size;
            if (index == 0) {
                cols = inputs;
            }
            if (index == num_layers-2) {
                rows = outputs;
            }
            for (unsigned i = 0; i < rows; ++i) {
                for (unsigned j = 0; j < cols; ++j) {
                    std::cout << adjacency_matrices[index][i][j] << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }
        std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------\n";
    }
private:
    float fRand(float fMin, float fMax) {
        float f = (float)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    void init_layer(unsigned index, unsigned rows, unsigned cols) {
        for (unsigned i = 0; i < rows; ++i) {
            adjacency_matrices[index][i] = new float[cols];
            for (unsigned j = 0; j < cols; ++j) {
                adjacency_matrices[index][i][j] = fRand(-1,1);
            }
        }
    }

    void init_nodes(unsigned index, unsigned layer_size) {
        for (unsigned i = 0; i < layer_size; ++i) {
            if (index == 0) {
                biases[index][i] = 0.0;
            }
            else {
                biases[index][i] = fRand(-1,1);
            }
            activations[index][i] = 0.0;
            //std::cout << biases[index][i] << " | ";
        }
        //std::cout << "\n";
    }

    float ReLU(float x) {
        if (x < 0) {
            return 0.0;
        }
        else {
            return x;
        }
    }


};

#endif