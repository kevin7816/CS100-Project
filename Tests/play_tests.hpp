#ifndef __PLAYTESTS_H__
#define __PLAYTESTS_H__

#include <iostream>
#include "tests.hpp"
#include "../GameMode/Play.hpp"

class PlayTests : public Tests {
    private: 
        Play play;
    public:
        // ~PlayTests() { }
        virtual void run_tests() {
            SDL_Renderer* renderer;

            constructor_test(renderer);
            serve_test(0);
            serve_test(1);

            cout << "-------------------\n"
                << "Passed " << passed << " tests\n"
                << "Failed " << failed << " tests\n"
                << "-------------------\n";

            return;
        }

        void constructor_test(SDL_Renderer* renderer) { 
            if (play.left_controller == nullptr || play.left_paddle == nullptr ||
                play.right_controller == nullptr || play.right_paddle == nullptr ||
                play.ball == nullptr) {
                failed++;
                cout << "[FAILED] Setup_Test: Failed to set up game objects\n"
                     << "       Expected: paddles are created and assigned to controllers; ball is created\n"
                     << "       Actual: some object pointers are still null\n";
            } else {
                passed++;
                cout << "[PASSED] Setup_Test: All game objects are created" << endl;
            }
            cout << endl;
            return;
        }

        void serve_test(const bool &turn) {
            bool cpy = turn;
            play.serve(cpy);
            if (cpy == 1) { // turn is switched after calling serve()
                if (play.ball->getVelX() != play.ball->getSpeed()/-2) {
                    failed++;
                    cout << "[FAILED] Serve_Test: Failed to set the server\n"
                         << "       Expected: Right paddle's turn to serve\n"
                         << "       Actual: Ball does not start from the right\n";
                } else {
                    passed++;
                    cout << "[PASSED] Serve_Test: Server is correctly set to right paddle" << endl;
                }
            }
            else if (cpy == 0) {
                if (play.ball->getVelX() != play.ball->getSpeed()/2) {
                    failed++;
                    cout << "[FAILED] Serve_Test: Failed to set the server\n"
                         << "       Expected: Left paddle's turn to serve\n"
                         << "       Actual: Ball does not start from the left\n";
                } else {
                    passed++;
                    cout << "[PASSED] Serve_Test: Server is correctly set to left paddle" << endl;
                }
            }
            if (cpy == turn) {
                failed++;
                cout << "[FAILED] Serve_Test: Failed to switch the server\n"
                        << "       Expected: Turn is switched after calling serve()\n"
                        << "       Actual: Turn stays the same\n";
            } else {
                passed++;
                cout << "[PASSED] Serve_Test: Turn is successfully switched" << endl;
            }

            cout << endl;
            return;            
        }

};

#endif


//g++ play_tests.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/play_test