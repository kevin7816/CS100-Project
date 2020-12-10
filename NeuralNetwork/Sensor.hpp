#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include "../Pong/Ball.hpp"
#include "../definitions.hpp"
#include <iostream>

class Sensor {
private:
    Ball* ball;
public:
    Sensor(Ball* ball): ball(ball) {}

    void set_activations(Player* player, float* activations, unsigned inputs) {
        switch (inputs) {
            case 3:
                //set_3_activations(player, activations);
                op_3(player, activations);
                break;
            case 4:
                set_4_activations(player, activations);
                break;
            case 5:
                set_5_activations(player, activations);
                break;
            case 6:
                set_6_activations(player, activations);
                break;
            default:
                throw("the neural network does not have the correct ammount of inputs\n");
        }
    }

    void set_ball(Ball* ball) { this->ball = ball; }
private:
    void set_3_activations(Player* player, float* activations) {
        activations[0] = normalize(ball->getX(), 32, WIDTH - 32);
        // cout << activations[0] << endl;
        activations[1] = normalize(ball->getY(), 0, HEIGHT);
        activations[2] = normalize(player->getY(), 0, HEIGHT);
    }

    void op_3(Player* player, float* activations) {
        float x_guess = ball->getX();
        float y_guess = ball->getY();
        float velY = ball->getVelY();
        // cout << activations[0] << endl;
        // cout << ball->getVelX() << ' ' << ball->getX() << endl;
        if (ball->getVelX() > 0 && ball->getX() < player->getX()) {
            while (x_guess < player->getX()) {
                if (y_guess <= 0 || y_guess >= HEIGHT) {
                    velY = -velY;
                }
                y_guess += velY;
                x_guess += ball->getVelX();
            }
            // cout << activations[0] << endl;
            activations[0] = normalize(ball->getX(), 32, WIDTH - 32);
            // cout << activations[0] << endl;
            activations[1] = normalize(y_guess, 0, HEIGHT);
            activations[2] = normalize(player->getY(), 0, HEIGHT);
        }
        else {
            activations[0] = 0;
            activations[1] = 0;
            activations[2] = normalize(player->getY(), 0, HEIGHT);
        }
    }

    void set_4_activations(Player* player, float* activations) {
        activations[0] = normalize(ball->getX(), 32, WIDTH - 32);
        //cout << activations[0] << endl;
        activations[1] = normalize(ball->getY(), 0, HEIGHT);
        activations[2] = normalize(player->getY(), 0, HEIGHT);
        activations[3] = normalize(ball->getVelX(), -BALL_SPEED + 2, BALL_SPEED - 2);
    }

    void set_5_activations(Player* player, float* activations) {
        activations[0] = normalize(ball->getX(), 32, WIDTH - 32);
        activations[1] = normalize(ball->getY(), 0, HEIGHT);
        activations[2] = normalize(ball->getVelX(), -BALL_SPEED + 2, BALL_SPEED - 2);
        activations[3] = normalize(ball->getVelY(), -BALL_SPEED + 2, BALL_SPEED - 2);
        activations[4] = normalize(player->getY(), 0, HEIGHT);

        // for (unsigned i = 0; i < 5; ++i) {
        //     std::cout << activations[i] << ' ';
        // }
        // std::cout << std::endl;
    }

    void set_6_activations(Player* player, float* activations) {
        activations[0] = normalize(ball->getX(), 32, WIDTH - 32);
        activations[1] = normalize(ball->getY(), 0, HEIGHT);
        activations[2] = ball->getSpeed();
        activations[3] = normalize(ball->getVelX(), -BALL_SPEED, BALL_SPEED);
        activations[4] = normalize(ball->getVelY(), -BALL_SPEED, BALL_SPEED);
        activations[5] = normalize(player->getY(), 0, HEIGHT);
    }

    template<typename T, typename U, typename V>
    float normalize(T x, U min, V max) {
        return ((float)x - min) / ((float)max - min);
    }
};

#endif
