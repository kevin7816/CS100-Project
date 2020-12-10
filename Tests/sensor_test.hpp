#ifndef __SENSORTESTS_H__
#define __SENSORTESTS_H__

#include <iostream>
#include "tests.hpp"
#include "../NeuralNetwork/Sensor.hpp"
#include "../Pong/Player.hpp"
#include "../Pong/USer.hpp"

class SensorTests : public Tests {
    private:
        Sensor* sensor = new Sensor(new Ball());
        const char* err_msg = "";
    public:
        virtual void run_tests() {
            set_activations_test();

            std::cout << "-------------------\n";
            SetColor(2);
            std::cout << "Passed " << passed << " tests\n";
            SetColor(4);
            std::cout << "Failed " << failed << " tests\n";
            SetColor(7);
            std::cout << "-------------------\n";

            delete sensor;

            return;
        }

        void set_activations_test() { 
            Player* player = new Player(new User(SDL_SCANCODE_W, SDL_SCANCODE_S), 0, 0, 10, 10);

            float act3[3] = {-1, -1, -1};
            int inputs = 3;
            sensor->set_activations(player, act3, inputs);

            if (act3[0] == -1 || act3[1] == -1 || act3[2] == -1) {
                failed++;
                std::cout << "[FAILED] Set_Activation: Failed to set activation for 3 inputs\n"
                          << "       Expected: float pointers array's elements should all be set to non-negative values\n"
                          << "       Actual: some elements are still -1\n";

            } else {
                passed++;
                std::cout << "[PASSED] Set_Activation: Successfully set activation for 3 inputs" << std::endl;
            }

            float act4[4] = {-1, -1, -1, -1};
            inputs = 4;
            sensor->set_activations(player, act4, inputs);

            if (act4[0] == -1 || act4[1] == -1 || act4[2] == -1 || act4[3] == -1) {
                failed++;
                std::cout << "[FAILED] Set_Activation: Failed to set activation for 4 inputs\n"
                          << "       Expected: float pointers array's elements should all be set to non-negative values\n"
                          << "       Actual: some elements are still -1\n";

            } else {
                passed++;
                std::cout << "[PASSED] Set_Activation: Successfully set activation for 4 inputs" << std::endl;
            }

            float act5[5] = {-1, -1, -1, -1, -1};
            inputs = 5;
            sensor->set_activations(player, act5, inputs);

            if (act5[0] == -1 || act5[1] == -1 || act5[2] == -1 || act5[3] == -1 || act5[4] == -1) {
                failed++;
                std::cout << "[FAILED] Set_Activation: Failed to set activation for 5 inputs\n"
                          << "       Expected: float pointers array's elements should all be set to non-negative values\n"
                          << "       Actual: some elements are still -1\n";

            } else {
                passed++;
                std::cout << "[PASSED] Set_Activation: Successfully set activation for 5 inputs" << std::endl;
            }

            float act6[6] = {-1, -1, -1, -1, -1, -1};
            inputs = 6;
            sensor->set_activations(player, act6, inputs);

            if (act6[0] == -1 || act6[1] == -1 || act6[2] == -1 || act6[3] == -1 || act6[4] == -1 || act6[5] == -1) {
                failed++;
                std::cout << "[FAILED] Set_Activation: Failed to set activation for 6 inputs\n"
                     << "       Expected: float pointers array's elements should all be set to non-negative values\n"
                     << "       Actual: some elements are still -1\n";

            } else {
                passed++;
                std::cout << "[PASSED] Set_Activation: Successfully set activation for 6 inputs" << std::endl;
            }

            float act1[1] = {-1};
            inputs = 1;

            try {
                sensor->set_activations(player, act1, inputs);
            }
            catch (const char* msg) {
                err_msg = msg;
            }
            if (err_msg != "the neural network does not have the correct ammount of inputs\n") {
                failed++;
                std::cout << "[FAILED] Set_Activation_Fail_1: Did not fail as expected" << std::endl
                          << "       Expect: Error message \"the neural network does not have the correct ammount of inputs\"\n";
            } else {
                passed++;
                std::cout << "[PASSED] Set_Activation_Fail_1: Failed as expected" << std::endl;
            }

            float act10[10] = {-1};
            inputs = 10;

            try {
                sensor->set_activations(player, act10, inputs);
            }
            catch (const char* msg) {
                err_msg = msg;
            }
            if (err_msg != "the neural network does not have the correct ammount of inputs\n") {
                failed++;
                std::cout << "[FAILED] Set_Activation_Fail_10: Did not fail as expected" << std::endl
                     << "       Expect: Error message \"the neural network does not have the correct ammount of inputs\"\n";
            } else {
                passed++;
                std::cout << "[PASSED] Set_Activation_Fail_10: Failed as expected" << std::endl;
            }

            if (!player) {
                delete player;
            }

            std::cout << std::endl;
            return;
        }
};

#endif