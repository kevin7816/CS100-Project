// #include "Layer.h"
#include "Matrix.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <ctime>

using namespace std;

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
    NetworkParams params(10,3,3,5);

    NeuralNetwork* nn1 = new NeuralNetwork(params);
    NeuralNetwork* nn2 = new NeuralNetwork(params);

    nn1->forward_propagation();

    cout << "nn1-----------------------------------------------------------------------------" << endl;
    nn1->print_weights();
    cout << endl;

    cout << "nn2-----------------------------------------------------------------------------" << endl;
    nn2->print_weights();
    cout << endl;

    NeuralNetwork* child = new NeuralNetwork(params, nn1, nn2, 0.05);
    cout << "child-----------------------------------------------------------------------------" << endl;
    child->print_weights();

    delete nn1;
    delete nn2;
    delete child;


    return 0;
}
