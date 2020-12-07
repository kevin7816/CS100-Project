#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Object.hpp"
#include "Controller.hpp"
#include "Player.hpp"
#include "User.hpp"
#include "Ball.hpp"
#include "Text.hpp"
#include "GameRenderer.hpp"
#include "../NeuralNetwork/Sensor.hpp"
#include "../NeuralNetwork/AI.hpp"
#include "../NeuralNetwork/NetworkHandler.hpp"

#include <ctime>
#include <math.h>

#include "../definitions.hpp"

// float fRand(float fMin, float fMax) {
//     float f = (float)rand() / RAND_MAX;
//     return fMin + f * (fMax - fMin);
// }

int main(int argc, char * argv[]) {
    srand(time(0));

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Pong",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,0);
    if(!window) {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(!renderer) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    NetworkParams params(5,3,1,15);

    Player** players;
    Ball** balls;
    unsigned total = 0;
    while (1) {
        players = new Player*[200];
        balls = new Ball*[200];
        for (unsigned i = 0; i < 200; ++i) {
            balls[i] = new Ball();
            players[i] = new Player(new AI(new Sensor(balls[i]), params), 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
            players[i]->randomize_color();
            players[i]->get_input();
        }


        NeuralNetwork** saved = new NeuralNetwork*[10];
        for (unsigned i = 0; i < 10; ++i) {
            saved[i] = new NeuralNetwork(players[i]->getController()->getNetwork(), params);
        }
        for (unsigned i = 0; i < 200; ++i) {
            delete players[i];
            delete balls[i];
        }
        delete [] balls;
        delete [] players;
        for (unsigned i = 0; i < 10; ++i) {
            saved[i]->forward_propagation();
        }
        cout << total << endl;

        players = new Player*[200];
        balls = new Ball*[200];
        //cout << "going forward_propagation" << endl;
        for (unsigned i = 0; i < 200; ++i) {
            balls[i] = new Ball();
            unsigned dad_index = fRand(0, 10-1);
            unsigned mom_index = fRand(0, 10-1);

            //cout << dad_index << ' ' << mom_index << " done" << endl;
            AI* child = new AI(new Sensor(balls[i]), params, saved[dad_index], saved[mom_index], 0.05);

            child->getNetwork()->forward_propagation();
            //cout << "done2" << endl;
            players[i] = new Player(child, 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/HEIGHT_RATIO),12);
            // cout << "going forward_propagation" << endl;
            players[i]->getController()->getNetwork()->forward_propagation();
            //cout << "done3" << endl;

        }


        for (unsigned i = 0; i < 200; ++i) {
            delete players[i];
            delete balls[i];
        }
        for (unsigned i = 0; i < 10; ++i) {
            delete saved[i];
        }
        delete [] balls;
        delete [] players;
        delete [] saved;
        //cout << "loop" << endl;
        ++total;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//g++ pong.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/test

//g++ test.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/testing
