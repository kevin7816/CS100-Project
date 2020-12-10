#ifndef __BALLTESTS_H__
#define __BALLTESTS_H__

#include <iostream>
#include "../Pong/Ball.hpp"
#include "tests.hpp"

using namespace std;

class BallTests : public Tests {
    private: 
        Ball* ball;
    public:
        virtual void run_tests() {
            // constructors test
            ball = new Ball();
            constructor_tests(1, ball, ball->getX(), ball->getY(), ball->getH(), ball->getW());
            delete ball;

            ball = new Ball(10, 20);
            constructor_tests(2, ball, ball->getX(), ball->getY(), ball->getH(), ball->getW());
            delete ball;

            // functions test
            ball = new Ball();
            function_tests(ball);
            delete ball;

            ball = new Ball(10, 20);
            function_tests(ball);
            delete ball;

            std::cout << "-------------------\n";
            SetColor(2);
            std::cout << "Passed " << passed << " tests\n";
            SetColor(4);
            std::cout << "Failed " << failed << " tests\n";
            SetColor(7);
            std::cout << "-------------------\n";

            return;
        }

        void constructor_tests(int num, Ball* ball, int x, int y, int h, int w) {
            if (ball->getX() != x) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Ball X\n"
                    << "       Expected: x == " << x << "\n"
                    << "       Actual: " << ball->getX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Ball X" << endl;
            }
            if (ball->getY() != y) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Ball Y\n"
                    << "       Expected: y == " << y << "\n"
                    << "       Actual: " << ball->getY() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Ball y" << endl;
            }
            if (ball->getH() != h) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Ball H\n"
                    << "       Expected: h == " << h << "\n"
                    << "       Actual: " << ball->getH() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Ball H" << endl;
            }
            if (ball->getW() != w) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Ball W\n"
                    << "       Expected: W == " << w << "\n"
                    << "       Actual: " << ball->getW() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Ball W" << endl;
            }
            
            cout << endl;
            return;
        }

        void function_tests(Ball* ball) {
            ball->setX(2);
            if (ball->getX() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_X: Failed changing ball's x" << endl
                    << "       Expect: x == 2\n"
                    << "       Actual: x ==" << ball->getX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_X: Ball's x is changed" << endl;
            }

            ball->setY(2);
            if (ball->getY() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_Y: Failed changing ball's y" << endl
                    << "       Expect: y == 2\n"
                    << "       Actual: y ==" << ball->getX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_Y: Ball's y is changed" << endl;
            }

            ball->setH(2);
            if (ball->getH() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_H: Failed changing ball's h" << endl
                    << "       Expect: h == 2\n"
                    << "       Actual: h ==" << ball->getH() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_H: Ball's h is changed" << endl;
            }

            ball->setW(2);
            if (ball->getW() != 2) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_W: Failed changing ball's w" << endl
                    << "       Expect: w == 2\n"
                    << "       Actual: w ==" << ball->getW() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_W: Ball's w is changed" << endl;
            }

            ball->setSpeed(23);
            if (ball->getSpeed() != 23) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_Speed: Failed changing ball's speed" << endl
                    << "       Expect: speed == 23\n"
                    << "       Actual: speed ==" << ball->getSpeed() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_Speed: Ball's speed is changed" << endl;
            }

            ball->setVelX(7);
            if (ball->getVelX() != 7) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_VelX: Failed changing ball's x velocity" << endl
                    << "       Expect: velx == 7\n"
                    << "       Actual: velx ==" << ball->getVelX() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_Velx: Ball's x velocity is changed" << endl;
            }

            cout << endl;
            return;
        }

        
};

#endif