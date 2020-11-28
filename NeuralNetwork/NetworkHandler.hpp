#ifndef __NETWORK_HANDLER_H__
#define __NETWORK_HANDLER_H__

#include "NeuralNetwork.hpp"
#include "../Pong/Ball.hpp"
#include "../Pong/Player.hpp"
#include "Sensor.hpp"
#include "AI.hpp"

#include <vector>
#include <math.h>

class NetworkHandler {
private:
    NetworkParams network_params;
    float mutation_rate;
    unsigned generation_size;

    Ball** balls;
    Sensor** sensors; //sensor holds ball
    AI** ais; //ai holds sensor
    Player** players; //player holds ai

public:
    NetworkHandler(unsigned inputs, unsigned outputs, unsigned hidden_layers, unsigned hidden_layer_size, float mutation_rate, unsigned generation_size):
    mutation_rate(mutation_rate), generation_size(generation_size) {
        network_params.inputs = inputs;
        network_params.outputs = outputs;
        network_params.hidden_layers = hidden_layers;
        network_params.hidden_layer_size = hidden_layer_size;
    }
    NetworkHandler(NetworkParams & params, float mutation_rate, unsigned generation_size):
    NetworkHandler(params.inputs, params.outputs, params.hidden_layers, params.hidden_layer_size, mutation_rate, generation_size) {}

    void init_networks() {
        ais = new AI*[generation_size];
        balls = new Ball*[generation_size];
        sensors = new Sensor*[generation_size];
        players = new Player*[generation_size];
        for (unsigned i = 0; i < generation_size; ++i) {
            balls[i] = new Ball();
            sensors[i] = new Sensor(balls[i]);
            ais[i] = new AI(sensors[i], network_params);
            players[i] = new Player(ais[i], 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
            players[i]->randomize_color();
        }
    }

    void update() {
        for (unsigned i = 0; i < generation_size; ++i) {
            if (players[i]) {
                update(players[i], balls[i]);
                players[i]->get_input();
            }
        }
    }

    // void get_input() {
    //     for (unsigned i = 0; i < generation_size; ++i) {
    //         if (players[i]) {
    //             players[i]->get_input();
    //         }
    //     }
    // }

    Ball** getBalls() {
        return balls;
    }
    unsigned size() {
        return generation_size;
    }

    vector<Object*> getObjects() {
        vector<Object*> objects;
        for (unsigned i = 0; i < generation_size; ++i) {
            if (players[i]) {
                objects.push_back(players[i]);
                objects.push_back(balls[i]);
            }
        }
        return objects;
    }

    void serve() {
        for (unsigned i = 0; i < generation_size; ++i) {
            players[i]->setX(WIDTH-32);

            balls[i]->setX(players[i]->getX()+(players[i]->getW()*4));
            balls[i]->setVelX(balls[i]->getSpeed()/-2);

            balls[i]->setVelY(0);
            balls[i]->setY((HEIGHT/2)-8);
        }
    }
private:
    void update(Player* paddle, Ball* ball) {
        SDL_Rect b = ball->getRect();
        SDL_Rect p = paddle->getRect();
        if(SDL_HasIntersection(&b, &p)){                                                  //checks if ball and paddle interact
            double rel = (paddle->getY()+(paddle->getH()/2))-(ball->getY()+8);
            double norm = rel/(paddle->getH()/2);
            double bounce = norm * (5*PI/12);
            ball->setVelX((ball->getSpeed()*-1)*cos(bounce));                               //sends ball at different angle based on where the ball has hit the paddle
            ball->setVelY((ball->getSpeed())*-sin(bounce));
        }

        if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);       //check to see if ball hit top or bottom walls
        ball->setX(ball->getVelX()+ball->getX());                                               //ball movement;
        ball->setY(ball->getVelY()+ball->getY());

        if(paddle->getY()<0) paddle->setY(0);                                       // boundaries for paddles
        if(paddle->getY() + paddle->getH()>HEIGHT) paddle->setY(HEIGHT-paddle->getH());

        if(ball->getX()+16>=WIDTH) kill(paddle, ball);
    }

    void kill(Player* paddle, Ball* ball) {
        for (unsigned i = 0; i < generation_size; ++i) {
            if (players[i] == paddle) {
                delete players[i];
                delete balls[i];
                delete sensors[i];
                delete ais[i];

                players[i] = nullptr;
                balls[i] = nullptr;
                sensors[i] = nullptr;
                ais[i] = nullptr;
                break;
            }
        }
    }
};

#endif
