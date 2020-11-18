#ifndef __MATRIX_H__
#define __MATRIX_H__

class Matrix {
public:
    /*
    the cols of arr have to be the same as the rows of arr2
    ex

    1 2 3   10
    4 5 6   20
            30

    return length = rows of arr
    */
    static float* multiply(float** arr, float* arr2, unsigned rows, unsigned cols) {
        float* return_arr = new float[rows];
        for (unsigned i = 0; i < rows; ++i) {
            float running_sum = 0;
            for (unsigned j = 0; j < cols; ++j) {
                running_sum += arr[i][j] * arr2[j];
            }
            return_arr[i] = running_sum;
        }
        return return_arr;
    }
};

#endif
