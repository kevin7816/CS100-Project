#ifndef __GAMEMODE_HPP__
#define __GAMEMODE_HPP__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "../Pong/GameRenderer.hpp"
#include "../definitions.hpp"

#include <ctime>

class Gamemode {
protected:
    SDL_Renderer *renderer;
    SDL_Window *window;

    GameRenderer gameRend;

    int frameCount, timerFPS, lastFrame, fps;
    int lastTime;
public:
    Gamemode(): lastTime(0) {
        srand(time(0));

        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
            fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
            throw("Could not init SDL\n");
        }
        window = SDL_CreateWindow("Pong",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,0);
        if(!window) {
            fprintf(stderr, "Could not create window\n");
            throw("Could not create window\n");
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if(!renderer) {
            fprintf(stderr, "Could not create renderer\n");
            throw("Could not create renderer\n");
        }

        gameRend = GameRenderer();
    }
    virtual ~Gamemode() {}
    virtual void update(bool &) = 0;
};

#endif
