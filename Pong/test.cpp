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

    NetworkParams params(5,3,1,10);

    Player** players;
    Ball** balls;
    while (1) {
        players = new Player*[200];
        balls = new Ball*[200];
        for (unsigned i = 0; i < 200; ++i) {
            balls[i] = new Ball();
            players[i] = new Player(new AI(new Sensor(balls[i]), params), 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
            players[i]->randomize_color();
            players[i]->get_input();
        }

        for (unsigned i = 0; i < 200; ++i) {
            delete players[i];
            delete balls[i];
        }

        delete [] balls;
        delete [] players;
        //cout << "loop" << endl;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//g++ pong.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/test

//g++ test.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/testing
