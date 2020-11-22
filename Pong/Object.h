#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "SDL2/SDL.h"

class Object {
    private:
        double x;
        double y;
    public:
        Object() {
            x=0.0;
            y=0.0;
        }
        Object(double x, double y){
            this->x=x;
            this->y=y;
        }
        virtual void show(SDL_Renderer* renderer) = 0;
};

#endif