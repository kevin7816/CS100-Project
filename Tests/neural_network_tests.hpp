#ifndef __NEURAL_NETWORK_TESTS_H__
#define __NEURAL_NETWORK_TESTS_H__

#include "../NeuralNetwork/NeuralNetwork.hpp"
#include <iostream>
#include "tests.hpp"

class NeuralNetworkTests : public Tests {
    private:

    public:
        virtual void run_tests() {
            constructor();
            
            std::cout << "-------------------\n";
            SetColor(2);
            std::cout << "Passed " << passed << " tests\n";
            SetColor(4);
            std::cout << "Failed " << failed << " tests\n";
            SetColor(7);
            std::cout << "-------------------\n";

            return;
        }

         void constructor(){
            NeuralNetwork* test = new NeuralNetwork(3,2,1,1);
            float* input = test->get_inputs();
            if (*input!= 0){
                 std::cout << "[FAILED] get_input(): Failed to return correct value\n"
                      << "       Expected: 0 is returned\n"
                      << "       Actual: " << *input << " is returned\n";
                     failed++;
             }
            else{
                passed++;
                 std::cout << "[PASSED] get_input(): " << *input << " is correctly returned\n";
             }
            float* output = test->get_outputs();
            if (*output != 0){
                std::cout << "[FAILED] get_input(): Failed to return correct value\n"
                      << "       Expected: 0 is returned\n"
                      << "       Actual: " << *output << " is returned\n";
                     failed++;
             }
            else{
                passed++;
                 std::cout << "[PASSED] get_input(): " << *output << " is correctly returned\n";
            }
            delete test;
         }
};


#endif
 