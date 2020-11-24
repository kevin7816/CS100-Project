#ifndef __BALL_H__
#define __BALL_H__


#include "sdl2lib/include/SDL2/SDL.h"
#include "Object.hpp"

class Ball : public Object {
    private:
        double speed=16.0;
        double velX=0;
        double velY=0;
        SDL_Rect rect;
    public:
        Ball() : Object(this) {
            rect.x=0;
            rect.y=0;
            rect.h=16;
            rect.w=16;
        }
        Ball(double x, double y) : Object(this){
            rect.x=x;
            rect.y=y;
            rect.h=16;
            rect.w=16;
        }
        double getH(){
            return rect.h;
        } 
        void setH(double h){
            rect.h=h;
        }
        double getX(){
            return rect.x;
        } 
        void setX(double x){
            rect.x=x;
        }
        double getY(){
            return rect.y;
        } 
        void setY(double y){
            rect.y=y;
        }
        double getW(){
            return rect.w;
        } 
        void setW(double w){
            rect.w=w;
        }
        void setSpeed(double speed){
            this->speed=speed;
        }
        double getSpeed(){
            return speed;
        }
        void setVelX(double x){
            velX=x;
        }
        double getVelX(){
            return velX;
        }
        void setVelY(double y){
            velY=y;
        }
        double getVelY(){
            return velY;
        }
        void show(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        SDL_Rect getRect(){
            return rect;
        }

};

#endif