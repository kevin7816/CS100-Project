#ifndef __AITESTS_H__
#define __AITESTS_H__

#include <iostream>
#include "tests.hpp"
#include "../NeuralNetwork/AI.hpp"
#include "../Pong/Ball.hpp"

class AITests : public Tests {
    private: 
        AI* ai;
        Sensor* sensor;
        NeuralNetwork* nn;
        NetworkParams params;
    public:
        // ~AITests() {
        //     if (!ai) {
        //         delete ai;
        //     }
        //     delete sensor;
        //     delete nn;
        // }
        virtual void run_tests() {
            sensor = new Sensor(new Ball());
            nn = new NeuralNetwork(0,0,0,0);

            ai = new AI(sensor, nn);
            constructor_test();
            delete ai;

            ai = new AI(sensor, params);
            constructor_test();
            delete ai;

            get_network_test();
            // get_fitness_test();

            cout << "-------------------\n";
            SetColor(2);
            cout << "Passed " << passed << " tests\n";
            SetColor(4);
            cout << "Failed " << failed << " tests\n";
            SetColor(7);
            cout << "-------------------\n";

            delete sensor;
            delete nn;

            return;
        }

        void constructor_test() { 
            bool is_movement = false;

            if (ai->sensor == nullptr || ai->nn == nullptr) {
                failed++;
                cout << "[FAILED] Init_AI: Failed to initialize sensor and neural network\n"
                     << "       Expected: Sensor and NeuralNetwork pointers are created\n"
                     << "       Actual: some object pointers are still null\n";
            } else {
                passed++;
                cout << "[PASSED] Init_AI: Everything is created" << endl;
            }
            cout << endl;

            for (unsigned i = 0; i < nn->get_params().inputs; ++i) {
                if (ai->movement[i] == true) {
                    is_movement = true;
                    break;
                } 
            }
            if (is_movement) {
                failed++;
                cout << "[FAILED] Init_AI: Failed to set all movements to false\n";
            } else {
                passed++;
                cout << "[PASSED] Init_AI: All movements are false" << endl;
            }
            cout << endl;
            return;
        }

        void get_network_test() {
            nn = nullptr;
            ai->getNetwork();

            if (ai->nn == nullptr) {
                failed++;
                cout << "[FAILED] Get_Network: Failed to get neural network\n"
                     << "       Expected: neural network pointer is not null\n";
            } else {
                passed++;
                cout << "[PASSED] Get_Network: Successfully got neural network" << endl;
            }
            cout << endl;
        }

        // void get_fitness_test() {
        //     int fitness = -1;

        //     fitness = ai->get_fitness();

        //     if (fitness == -1) {
        //         failed++;
        //         cout << "[FAILED] Get_Fitness: Failed to get fitness\n"
        //              << "       Expected: fitness is not -1\n"
        //              << "       Actual: fitness is " << fitness << endl;
        //     } else {
        //         passed++;
        //         cout << "[PASSED] Get_Network: Successfully got fitness" << endl;
        //     }
        //     cout << endl;
        // }

};

#endif