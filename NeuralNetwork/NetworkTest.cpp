// #include "Layer.h"
#include "Matrix.h"
#include "NeuralNetwork.hpp"
#include <iostream>
#include <ctime>
// #include "AI.hpp"
// #include "Sensor.hpp"
// #include "../header/Ball.hpp"
#include "../definitions.hpp"

using namespace std;

template<typename T, typename U, typename V>
float normalize(T x, U min, V max) {
    return ((float)x - min) / ((float)max - min);
}

float fRand(float fMin, float fMax) {
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void set_3_activations(float* activations) {
    activations[0] = normalize(fRand(32, WIDTH - 32), 32, WIDTH - 32);
    activations[1] = normalize(fRand(0, HEIGHT), 0, HEIGHT);
    activations[2] = normalize(fRand(0, HEIGHT), 0, HEIGHT);
}

int main() {

    srand(time(0));
    // Layer new_Layer(5,5,5);
    // unsigned rows = 2;
    // unsigned cols = 3;
    //
    // float** arr = new float*[rows];
    // for (unsigned i =  0; i < rows; ++i) {
    //     arr[i] = new float[cols];
    // }
    // arr[0][0] = 1.0;
    // arr[0][1] = 2.0;
    // arr[0][2] = 3.0;
    //
    // arr[1][0] = 4.0;
    // arr[1][1] = 5.0;
    // arr[1][2] = 6.0;
    // /*
    // 1 2 3   10
    // 4 5 6   20
    //         30
    // */
    //
    // float arr2[cols] = {10.0, 20.0, 30.0};
    //
    // float* solution = Matrix::multiply(arr, arr2, rows, cols);
    // for (unsigned i =  0; i < rows; ++i) {
    //     std::cout << solution[i] << ' ';
    // }

    // NeuralNetwork nn(10,3,3,7);
    // nn.print_weights();
    // nn.print_activations();
    // nn.print_biases();
    // nn.forward_propagation();
    // nn.print_activations();
    // unsigned size = 100;
    //
    // NeuralNetwork** arr = new NeuralNetwork*[size];
    // for(unsigned i = 0; i < size; ++i) {
    //     NeuralNetwork* nn = new NeuralNetwork(10,3,3,40);
    //     arr[i] = nn;
    // }
    //
    // clock_t start = clock();
    // for(unsigned i = 0; i < size; ++i) {
    //     arr[i]->forward_propagation();
    // }
    // clock_t end = clock() - start;
    // std::cout << end << std::endl;

    unsigned inputs = 10;
    unsigned outputs = 3;
    unsigned hidden_layers = 3;
    unsigned hidden_layer_size = 5;
    NetworkParams params(3,3,10,3);

    // NeuralNetwork* nn1 = new NeuralNetwork(params);
    // NeuralNetwork* nn2 = new NeuralNetwork(params);
    //
    // for (unsigned i = 0; i < 90000; ++i) {
    //     set_3_activations(nn1->get_inputs());
    //     nn1->forward_propagation();
    // }
    //
    // cout << "nn1-----------------------------------------------------------------------------" << endl;
    // nn1->print_biases();
    // cout << endl;
    //
    // cout << "nn2-----------------------------------------------------------------------------" << endl;
    // nn2->print_biases();
    // cout << endl;
    //
    // NeuralNetwork* child = new NeuralNetwork(params, nn1, nn2, 0.05);
    // NeuralNetwork* copy = new NeuralNetwork(nn1, params);
    // cout << "child-----------------------------------------------------------------------------" << endl;
    // child->print_biases();
    // child->print_weights();
    //
    // for (unsigned i = 0; i < 90000; ++i) {
    //     set_3_activations(copy->get_inputs());
    //     copy->forward_propagation();
    //     set_3_activations(child->get_inputs());
    //     child->forward_propagation();
    // }

    NeuralNetwork* nn1 = new NeuralNetwork(params);
    NeuralNetwork* nn2 = new NeuralNetwork(params);
    NeuralNetwork* temp = nullptr;
    NeuralNetwork* temp2 = nullptr;

    NeuralNetwork** arr = new NeuralNetwork*[200];
    for (unsigned i = 0; i < 200; ++i) {
        arr[i] = nullptr;
    }

    while (1) {
        set_3_activations(nn1->get_inputs());
        set_3_activations(nn2->get_inputs());
        nn1->forward_propagation();
        nn2->forward_propagation();

        for (unsigned i = 0; i < 200; ++i) {
            if (arr[i]) {
                delete arr[i];
            }
            arr[i] = new NeuralNetwork(params);
        }

        temp = new NeuralNetwork(params, nn1, nn2, 0.05);
        temp2 = new NeuralNetwork(params, nn1, nn2, 0.05);

        delete nn1;
        delete nn2;
        nn1 = temp;
        nn2 = temp2;
    }


    delete nn1;
    delete nn2;
    // delete child;
    // delete copy;
    // delete grandchild;

    //AI* ai = new AI(new Sensor(new Ball()), network_params);


    return 0;
}
