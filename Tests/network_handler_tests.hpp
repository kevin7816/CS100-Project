#ifndef __NETWORKHANDLERTESTS_H__
#define __NETWORKHANDLERTESTS_H__

#include <iostream>
#include <vector>
#include "tests.hpp"
#include "../Pong/Object.hpp"
#include "../NeuralNetwork/NetworkHandler.hpp"

class NHTests : public Tests {
    private:
        NetworkHandler* nh = new NetworkHandler(3, 3, 1, 5, 0.05, 3);
        const char* err_msg = "";
    public:
        virtual void run_tests() {
            init_networks_test();
            getBalls_test();
            size_test();

            std::cout << "-------------------\n"
                << "Passed " << passed << " tests\n"
                << "Failed " << failed << " tests\n"
                << "-------------------\n";

            delete nh;

            return;
        }

        void init_networks_test() { 
            int i_num_gen = nh->num_generations;

            nh->init_networks();

            if (nh->generation_size != 3) {
                failed++;
                std::cout << "[FAILED] Init_Networks: Failed to set generation size\n"
                          << "       Expected: generation_size == 3\n"
                          << "       Actual: generation_size == " << nh->generation_size << endl;
            } else {
                passed++;
                std::cout << "[PASSED] Init_Networks: Generation size is 3 as expected" << std::endl;
            }

            bool is_ball_emp = 0;
            bool is_player_emp = 0;
            for (unsigned i = 0; i < nh->generation_size; ++i) {
                if (nh->balls[i] == nullptr) {
                    is_ball_emp = 1;
                    break;
                }
                if (nh->players[i] == nullptr) {
                    is_player_emp = 1;
                    break;
                }
            }

            if (is_ball_emp == 1) {
                failed++;
                std::cout << "[FAILED] Init_Networks: Failed to init balls\n"
                          << "       Expected: generation_size number of balls are created\n"
                          << "       Actual: some ball pointers are still null\n";
            } else {
                passed++;
                std::cout << "[PASSED] Init_Networks: All balls are initialized" << std::endl;
            }

            if (is_player_emp == 1) {
                failed++;
                std::cout << "[FAILED] Init_Networks: Failed to init players\n"
                          << "       Expected: generation_size number of players are created\n"
                          << "       Actual: some ball pointers are still null\n";
            } else {
                passed++;
                std::cout << "[PASSED] Init_Networks: All players are initialized" << std::endl;
            }

            if ((i_num_gen + 1) != nh->num_generations) {
                failed++;
                std::cout << "[FAILED] Init_Networks: num_generations is not increased\n"
                          << "       Expected: num_generator == " << i_num_gen << " + 1\n"
                          << "       Actual: num_generator == " << nh->num_generations << "\n";

            } else {
                passed++;
                std::cout << "[PASSED] Init_Networks: num_generations is correctly increased by 1" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

        void getBalls_test() {
            Ball** balls = nullptr;
            balls = nh->getBalls();

            if (balls == nullptr) {
                failed++;
                std::cout << "[FAILED] Get_Balls_Pointers: Failed to balls pointers\n"
                          << "       Expected: balls pointer is not null\n";
            } else {
                passed++;
                std::cout << "[PASSED] Get_Balls_Pointers: Successfully get balls pointers" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

        void size_test() {
            unsigned size = -1;
            size = nh->size();

            if (size == -1) {
                failed++;
                std::cout << "[FAILED] Get_Size: Failed to get generation size\n"
                          << "       Expected: size is not -1\n";
            } else {
                passed++;
                std::cout << "[PASSED] Get_Size: Successfully get generation size" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

        void get_nth_gen_test() {
            unsigned gen = -1;
            gen = nh->get_nth_generation();

            if (gen == -1) {
                failed++;
                std::cout << "[FAILED] Get_nth_Generation: Failed to get num generation\n"
                          << "       Expected: gen is not -1\n";
            } else {
                passed++;
                std::cout << "[PASSED] Get_nth_Generation: Successfully get num generation" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

};

#endif