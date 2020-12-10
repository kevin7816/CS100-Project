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
            sum();
            
            std::cout << "-------------------\n"
                << "Passed " << passed << " tests\n"
                << "Failed " << failed << " tests\n"
                << "-------------------\n";

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

         void sum(){
            NeuralNetwork* test1 = new NeuralNetwork(3,2,2,2);
            if(test1->summnation()!=-4){
                std::cout << "[FAILED] summnation(): Failed to return correct value\n"
                      << "       Expected: -4 is returned\n"
                      << "       Actual: " << test1->summnation() << " is returned\n";
                     failed++;
             }
            else{
                passed++;
                 std::cout << "[PASSED] summnation(): " << test1->summnation() << " is correctly returned\n";
            }
            delete test1;

            NeuralNetwork* test2 = new NeuralNetwork(5,5,5,5);
            if(test2->summnation()!=1){
                std::cout << "[FAILED] summnation(): Failed to return correct value\n"
                      << "       Expected: 1 is returned\n"
                      << "       Actual: " << test2->summnation() << " is returned\n";
                     failed++;
             }
            else{
                passed++;
                 std::cout << "[PASSED] summnation(): " << test2->summnation() << " is correctly returned\n";
            }
            delete test2;

            NeuralNetwork* test3 = new NeuralNetwork(2,3,4,5);
            if(test3->summnation()!=4){
                std::cout << "[FAILED] summnation(): Failed to return correct value\n"
                      << "       Expected: 4 is returned\n"
                      << "       Actual: " << test3->summnation() << " is returned\n";
                     failed++;
             }
            else{
                passed++;
                 std::cout << "[PASSED] summnation(): " << test3->summnation() << " is correctly returned\n";
            }
            delete test3;
         }
};


#endif
 