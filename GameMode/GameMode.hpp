#ifndef __GAMEMODE_H__
#define __GAMEMODE_H__

#include "../Pong/sdl2lib/include/SDL2/SDL.h"
#include <vector>

class GameMode {
    public:
        GameMode() {}

        // create game objects
        virtual void setup(SDL_Renderer* renderer) = 0;

        // render all objects on screen and run the game
        virtual void run_game(SDL_Renderer* renderer) = 0;

    private:
        // virtual void serve(bool &turn) = 0;
        // virtual void update(bool &turn) = 0;
        virtual void input(bool &running) = 0;
};

#endif