#ifndef __TRAINTESTS_H__
#define __TRAINTESTS_H__

#include <iostream>
#include "tests.hpp"
#include "../GameMode/Train.hpp"

class TrainTests : public Tests {
    private: 
        Train train;
    public:
        // ~TrainTests() {}
        virtual void run_tests() {
            SDL_Renderer* renderer;

            constructor_test(renderer);

            cout << "-------------------\n"
                << "Passed " << passed << " tests\n"
                << "Failed " << failed << " tests\n"
                << "-------------------\n";

            return;
        }

        void constructor_test(SDL_Renderer* renderer) { 
            if (train.left_wall == nullptr || train.handler == nullptr) {
                failed++;
                cout << "[FAILED] Setup_Test: Failed to set up game objects\n"
                     << "       Expected: NetwordHandler and Wall are created\n"
                     << "       Actual: some object pointers are still null\n";
            } else {
                passed++;
                cout << "[PASSED] Setup_Test: All game objects are created" << endl;
            }
            cout << endl;
            return;
        }

};

#endif