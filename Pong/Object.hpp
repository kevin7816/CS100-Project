#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "sdl2lib/include/SDL2/SDL.h"
#include <vector>

class Object {
    private:
        double x;
        double y;
        std::vector<Object*> gameObjects;
    public:
        Object() {
            // x=0.0;
            // y=0.0;
        }
        // this contructor will be called in derived classes' constructors -> new Object will be automatically added to gameObjects vector
        Object(Object* object) {  
            add(object);
        }
        // Object(double x, double y){
        //     this->x=x;
        //     this->y=y;
        // }
        virtual void show(SDL_Renderer* renderer) = 0;
        void add(Object* object) {
            gameObjects.push_back(object);
            return;
        };
};

#endif