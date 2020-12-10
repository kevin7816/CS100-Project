#ifndef __PLAYERTESTS_H__
#define __PLAYERTESTS_H__

#include <iostream>
#include "../Pong/Player.hpp"
#include "tests.hpp"

using namespace std;

class PlayerTests : public Tests {
    private: 
        Player* player;
        Controller* controller = nullptr;
    public:
        virtual void run_tests() {
            // constructors test
            player = new Player(controller, 10, 20, 30, 40);
            constructor_tests(1, player, player->getX(), player->getY(), player->getH(), player->getW());
            function_tests(player);
            delete player;

            std::cout << "-------------------\n";
            SetColor(2);
            std::cout << "Passed " << passed << " tests\n";
            SetColor(4);
            std::cout << "Failed " << failed << " tests\n";
            SetColor(7);
            std::cout << "-------------------\n";

            return;
        }

        void constructor_tests(int num, Player* player, int x, int y, int h, int w) {
            if (player->getX() != x) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: player X\n"
                    << "       Expected: x == " << x << "\n"
                    << "       Actual: " << player->getX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: player X" << endl;
            }
            if (player->getY() != y) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Player Y\n"
                    << "       Expected: y == " << y << "\n"
                    << "       Actual: " << player->getY() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: player y" << endl;
            }
            if (player->getH() != h) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: player H\n"
                    << "       Expected: h == " << h << "\n"
                    << "       Actual: " << player->getH() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: player H" << endl;
            }
            if (player->getW() != w) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: player W\n"
                    << "       Expected: W == " << w << "\n"
                    << "       Actual: " << player->getW() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: player W" << endl;
            }
            
            cout << endl;
            return;
        }

        void function_tests(Player* player) {
            player->setX(2);
            if (player->getX() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_X: Failed changing player's x" << endl
                    << "       Expect: x == 2\n"
                    << "       Actual: x ==" << player->getX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_X: player's x is changed" << endl;
            }

            player->setY(2);
            if (player->getY() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_Y: Failed changing player's y" << endl
                    << "       Expect: y == 2\n"
                    << "       Actual: y ==" << player->getX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_Y: player's y is changed" << endl;
            }

            player->setH(2);
            if (player->getH() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_H: Failed changing player's h" << endl
                    << "       Expect: h == 2\n"
                    << "       Actual: h ==" << player->getH() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_H: player's h is changed" << endl;
            }

            player->setW(2);
            if (player->getW() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_W: Failed changing player's w" << endl
                    << "       Expect: w == 2\n"
                    << "       Actual: w ==" << player->getW() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_W: player's w is changed" << endl;
            }

            cout << endl;
            return;
        }

        
};

#endif