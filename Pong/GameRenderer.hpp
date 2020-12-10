#ifndef __GAMERENDERER_H__
#define __GAMERENDERER_H__

#include "../sdl2lib/include/SDL2/SDL.h"
#include "Object.hpp"
#include <iostream>
#include <vector>

using namespace std;

class GameRenderer {
    friend class GRTests;
    private:
        std::vector<Object*> gameObjects;
    public:
        GameRenderer() { };

        void render_all(SDL_Renderer *renderer, int frameCount, int timerFPS, int lastFrame){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     //renders black screen
            SDL_RenderClear(renderer);

            for(unsigned i = 0; i < gameObjects.size(); i++){
                // if (dynamic_cast<Text*>(gameObjects.at(i))) {
                //     if (dynamic_cast<Text*>(gameObjects.at(i))->score.first == 0) { // score_left
                //         dynamic_cast<Text*>(gameObjects.at(i))->words = to_string(score_lelf).c_str();
                //     }
                //     else if (dynamic_cast<Text*>(gameObjects.at(i))->score.first == 1) { // score_right
                //         dynamic_cast<Text*>(gameObjects.at(i))->words = to_string(score_right).c_str();
                //     }
                // }
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
        void render_all(SDL_Renderer * renderer, int frameCount, int timerFPS, int lastFrame, vector<Object*> objects) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     //renders black screen
            SDL_RenderClear(renderer);

            for(unsigned i = 0; i < gameObjects.size(); i++){
                gameObjects.at(i)->show(renderer);
            }                // update screen all at once to prevent flickering

            frameCount++;                                   // implements frame cap
            timerFPS = SDL_GetTicks()-lastFrame;
            if(timerFPS<(1000/60)) {
                SDL_Delay((1000/60)-timerFPS);              // SDL_Delay() should go after SDL_RenderPresent() for for smoother moves
            }

            for (unsigned i = 0; i < objects.size(); ++i) {
                objects.at(i)->show(renderer);
            }
            objects.clear();

            SDL_RenderPresent(renderer);
        }

        void add(Object* object) {
            for (auto i : gameObjects) {
                if (i == object) { // object is already in vector
                    throw "Object is already in vector";
                    return;
                }
            }
            gameObjects.push_back(object);
            return;
        }
        void remove(Object* object) {
            for (unsigned i = 0; i < gameObjects.size(); i++) {
                if (gameObjects.at(i) == object) {
                    delete gameObjects.at(i);
                    gameObjects.erase(gameObjects.begin() + i);
                    return;
                }
            }
            throw "Object is not in vector";
            return;
        }
};

#endif
