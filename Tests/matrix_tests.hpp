#ifndef __MATRIXTESTS_H__
#define __MATRIXTESTS_H__

#include <iostream>
#include "tests.hpp"
#include "../NeuralNetwork/Matrix.h"

class MatrixTests : public Tests {
    private:
        Matrix m;
    public:
        // ~AITests() {
        //     if (!ai) {
        //         delete ai;
        //     }
        //     delete sensor;
        //     delete nn;
        // }
        virtual void run_tests() {
            ReLU_test();

            std::cout << "-------------------\n";
            SetColor(2);
            std::cout << "Passed " << passed << " tests\n";
            SetColor(4);
            std::cout << "Failed " << failed << " tests\n";
            SetColor(7);
            std::cout << "-------------------\n";

            return;
        }

        void ReLU_test() { 
            float x = 14;
            static float ret = m.ReLU(x);
            if (ret != 14) {
                failed++;
                std::cout << "[FAILED] ReLU_positive: Failed to return correct value\n"
                     << "       Expected: 14 is returned\n"
                     << "       Actual: " << ret << " is returned\n";

            } else {
                passed++;
                std::cout << "[PASSED] ReLU_positive: " << ret << " is correctly returned\n";
            }

            x = 0;
            ret = m.ReLU(x);
            if (ret != 0) {
                failed++;
                std::cout << "[FAILED] ReLU_zero: Failed to return correct value\n"
                     << "       Expected: 0 is returned\n"
                     << "       Actual: " << ret << " is returned\n";

            } else {
                passed++;
                std::cout << "[PASSED] ReLU_zero: " << ret << " is correctly returned\n";
            }

            x = -19;
            ret = m.ReLU(x);
            if (ret != 0) {
                failed++;
                std::cout << "[FAILED] ReLU_negative: Failed to return correct value\n"
                     << "       Expected: 0 is returned\n"
                     << "       Actual: " << ret << " is returned\n";

            } else {
                passed++;
                std::cout << "[PASSED] ReLU_negative: " << ret << " is correctly returned\n";
            }

            std::cout << std::endl;
            return;
        }

};

#endif