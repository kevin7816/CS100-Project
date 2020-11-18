// #include "Layer.h"
#include "Matrix.h"
#include "NeuralNetwork.h"
#include <iostream>

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

    NeuralNetwork nn(10,3,3,7);
    nn.print_weights();
    nn.print_activations();
    nn.print_biases();
    nn.forward_propagation();
    nn.print_activations();


    return 0;
}
