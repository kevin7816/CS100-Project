#ifndef __GAMERENDERER_H__
#define __GAMERENDERER_H__

#include "sdl2lib/include/SDL2/SDL.h"
#include "Object.hpp"
#include <iostream>
#include <vector>

class GameRenderer {
    private:
        std::vector<Object*> gameObjects;
    public:
        GameRenderer() { };

        void render_all(SDL_Renderer *renderer, int frameCount, int timerFPS, int lastFrame){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     //renders black screen
            SDL_RenderClear(renderer);

            for(unsigned i=0;i< gameObjects.size();i++){
                gameObjects.at(i)->show(renderer);
            }
            SDL_RenderPresent(renderer);                    // update screen all at once to prevent flickering

            frameCount++;                                   // implements frame cap
            timerFPS = SDL_GetTicks()-lastFrame;
            if(timerFPS<(1000/60)) {
                SDL_Delay((1000/60)-timerFPS);              // SDL_Delay() should go after SDL_RenderPresent() for for smoother moves
            }

            return;
        }
        // void render_all(SDL_Renderer * renderer, int frameCount, int timerFPS, int lastFrame, vector<Object*> objects) {
        //     render_all(renderer, frameCount, timerFPS, lastFrame);
        //     for (unsigned i = 0; i < objects.size(); ++i) {
        //         objects.at(i)->show(renderer);
        //     }
        // }
        void add(Object* object) {
            gameObjects.push_back(object);
            return;
        }
};

#endif
